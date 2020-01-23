#ifndef KSAKKRHOAKQLHVICENWKVLCUYIIOOVIFCDSDUTLUFRJBPJQEXPFBXDMFQVQHWMDEEYCFFXLAP
#define KSAKKRHOAKQLHVICENWKVLCUYIIOOVIFCDSDUTLUFRJBPJQEXPFBXDMFQVQHWMDEEYCFFXLAP

#include <cstddef>
#include <functional>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <algorithm>
			
namespace numeric
{

    struct simple_thread_pool
    {
        typedef std::function<void()>                                           function_type;

        std::atomic_bool                                                        all_done_flag;
        std::queue<function_type>                                               work_queue;
        mutable std::mutex                                                      work_queue_mutex;
        std::vector<std::thread>                                                thread_array;

        /*
        static thread_local std::size_t                                         local_thread_index;
        static std::queue<function_type>                                        local_work_queue;
        */

        simple_thread_pool( std::size_t max_threads_ = std::thread::hardware_concurrency() ) : all_done_flag{ false }
        {
            if ( max_threads_ < 2 ) 
                max_threads_ = 2;

            try
            {
                for ( std::size_t index = 0; index != max_threads_; ++index )
                    thread_array.push_back( std::thread{ &simple_thread_pool::work_loader, this } );
            }
            catch(...)
            {
                all_done_flag = true;
                throw;
            }
        }

        ~simple_thread_pool()
        {
            function_type remaining_work = nullptr;
            while ( true )
            {
                if ( try_pop_task( remaining_work ) )
                    remaining_work();
                else 
                    break;
            }

            all_done_flag = true;
            std::for_each(  thread_array.begin(), thread_array.end(), [](std::thread& the_thread)  { if ( the_thread.joinable() ) the_thread.join(); } );
        }

        template< typename Function >
        void submit_work( Function f_ )
        {
            std::lock_guard<std::mutex> lk{ work_queue_mutex };
            work_queue.push( function_type{f_} );
        }

        void work_loader()
        {
            function_type current_work = nullptr;
            while ( ! all_done_flag )
            {
                if ( try_pop_task( current_work ) )
                    current_work();
                else 
                    std::this_thread::yield();
            }
        }

        bool try_pop_task( function_type& f )
        {
            std::lock_guard<std::mutex> lg{ work_queue_mutex };
            if ( !work_queue.empty() )
            {
                f = std::move( work_queue.front() );
                work_queue.pop();
                return true;
            }
            return false;
        }

        simple_thread_pool( simple_thread_pool const& ) = delete;
        simple_thread_pool& operator = ( simple_thread_pool const& ) = delete;
        simple_thread_pool( simple_thread_pool && ) = delete;
        simple_thread_pool& operator = ( simple_thread_pool && ) = delete;

    };//struct simple_thead_pool

}//namespace numeric

#endif//KSAKKRHOAKQLHVICENWKVLCUYIIOOVIFCDSDUTLUFRJBPJQEXPFBXDMFQVQHWMDEEYCFFXLAP

