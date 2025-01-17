// 1 "e.cc"
// 1 "<built-in>" 1
// 1 "<built-in>" 3
// 394 "<built-in>" 3
// 1 "<command line>" 1
// 1 "<built-in>" 2
// 1 "e.cc" 2
// 1 "././expected.hpp" 1
// 93 "././expected.hpp"
//
//
#include <exception>
#include <functional>
#include <type_traits>
#include <utility>

namespace tl
{
    template <class T, class E>
    class expected;

    class monostate {};

    struct in_place_t
    {
        explicit in_place_t() = default;
    };

    static constexpr in_place_t in_place{};

    template <class E>
    class unexpected
    {
        public:
            static_assert( !std::is_same<E, void>::value, "E must not be void" );

            unexpected() = delete;

            constexpr explicit unexpected( const E& e ) : m_val( e ) {}

            constexpr explicit unexpected( E&& e ) : m_val( std::move( e ) ) {}


            constexpr const E& value() const&
            {
                return m_val;
            }

            constexpr E& value()& { return m_val; }

            constexpr E&& value()&& { return std::move( m_val ); }

            constexpr const E&& value() const&&
            {
                return std::move( m_val );
            }

        private:
            E m_val;
    };

    template <class E>
    constexpr bool operator==( const unexpected<E>& lhs, const unexpected<E>& rhs )
    {
        return lhs.value() == rhs.value();
    }

    template <class E>
    constexpr bool operator!=( const unexpected<E>& lhs, const unexpected<E>& rhs )
    {
        return lhs.value() != rhs.value();
    }

    template <class E>
    constexpr bool operator<( const unexpected<E>& lhs, const unexpected<E>& rhs )
    {
        return lhs.value() < rhs.value();
    }

    template <class E>
    constexpr bool operator<=( const unexpected<E>& lhs, const unexpected<E>& rhs )
    {
        return lhs.value() <= rhs.value();
    }

    template <class E>
    constexpr bool operator>( const unexpected<E>& lhs, const unexpected<E>& rhs )
    {
        return lhs.value() > rhs.value();
    }

    template <class E>
    constexpr bool operator>=( const unexpected<E>& lhs, const unexpected<E>& rhs )
    {
        return lhs.value() >= rhs.value();
    }

    template <class E>
    unexpected<typename std::decay<E>::type> make_unexpected( E&& e )
    {
        return unexpected<typename std::decay<E>::type>( std::forward<E>( e ) );
    }

    struct unexpect_t
    {
        unexpect_t() = default;
    };

    static constexpr unexpect_t unexpect{};

    namespace detail
    {
        template <class T>
        using remove_const_t = typename std::remove_const<T>::type;

        template <class T>
        using remove_reference_t = typename std::remove_reference<T>::type;

        template <class T>
        using decay_t = typename std::decay<T>::type;

        template <bool E, class T = void>
        using enable_if_t = typename std::enable_if<E, T>::type;

        template <bool B, class T, class F>
        using conditional_t = typename std::conditional<B, T, F>::type;

        template <class...>
        struct conjunction : std::true_type {};

        template <class B>
        struct conjunction<B> : B {};

        template <class B, class... Bs>
        struct conjunction<B, Bs...>
        : std::conditional<bool( B::value ), conjunction<Bs...>, B>::type {};

        template < typename Fn, typename... Args, typename = enable_if_t < std::is_member_pointer<decay_t<Fn>> {} >, int = 0 >
        constexpr auto invoke( Fn && f, Args && ... args ) noexcept( noexcept( std::mem_fn( f )( std::forward<Args>( args )... ) ) )
        -> decltype( std::mem_fn( f )( std::forward<Args>( args )... ) )
        {
            return std::mem_fn( f )( std::forward<Args>( args )... );
        }

        template < typename Fn, typename... Args, typename = enable_if_t < !std::is_member_pointer<decay_t<Fn>> {} >>
        constexpr auto invoke( Fn&& f, Args&& ... args ) noexcept( noexcept( std::forward<Fn>( f )( std::forward<Args>( args )... ) ) )
        -> decltype( std::forward<Fn>( f )( std::forward<Args>( args )... ) )
        {
            return std::forward<Fn>( f )( std::forward<Args>( args )... );
        }

        template <class F, class, class... Us>
        struct invoke_result_impl;

        template <class F, class... Us>
        struct invoke_result_impl < F, decltype( invoke( std::declval<F>(), std::declval<Us>()... ), void() ), Us... >
        {
            using type = decltype( invoke( std::declval<F>(), std::declval<Us>()... ) );
        };

        template <class F, class... Us>
        using invoke_result = invoke_result_impl<F, void, Us...>;

        template <class F, class... Us>
        using invoke_result_t = typename invoke_result<F, Us...>::type;

        template <class T>
        struct is_expected_impl : std::false_type {};

        template <class T, class E>
        struct is_expected_impl<expected<T, E>> : std::true_type {};

        template <class T>
        using is_expected = is_expected_impl<decay_t<T>>;

        template <class T, class E, class U>
        using expected_enable_forward_value = detail::enable_if_t <
            std::is_constructible < T, U && >::value &&
            !std::is_same<detail::decay_t<U>, in_place_t>::value &&
            !std::is_same<expected<T, E>, detail::decay_t<U>>::value &&
            !std::is_same<unexpected<E>, detail::decay_t<U>>::value >;

        template <class T, class E, class U, class G, class UR, class GR>
        using expected_enable_from_other = detail::enable_if_t <
            std::is_constructible<T, UR>::value &&
            std::is_constructible<T, GR>::value &&
            !std::is_constructible<T, expected<U, G> &>::value &&
            !std::is_constructible < T, expected<U, G>&& >::value &&
            !std::is_constructible<T, const expected<U, G> &>::value &&
            !std::is_constructible < T, const expected<U, G>&& >::value &&
            !std::is_convertible<expected<U, G> &, T>::value &&
            !std::is_convertible < expected<U, G>&&, T >::value &&
            !std::is_convertible<const expected<U, G> &, T>::value &&
            !std::is_convertible < const expected<U, G>&&, T >::value >;

        template <class T, class U>
        using is_void_or = conditional_t<std::is_void<T>::value, std::true_type, U>;

        template <class T>
        using is_copy_constructible_or_void = is_void_or<T, std::is_copy_constructible<T>>;

        template <class T>
        using is_move_constructible_or_void = is_void_or<T, std::is_move_constructible<T>>;
    }

    namespace detail
    {
        struct no_init_t {};
        static constexpr no_init_t no_init{};

        template <class T, class E, bool = std::is_trivially_destructible<T>::value, bool = std::is_trivially_destructible<E>::value>
        struct expected_storage_base
        {
            constexpr expected_storage_base() : m_val( T{} ), m_has_val( true ) {}
            constexpr expected_storage_base( no_init_t ) : m_has_val( false ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < T, Args&& ... >::value > * = nullptr >
            constexpr expected_storage_base( in_place_t, Args && ... args ) : m_val( std::forward<Args>( args )... ), m_has_val( true ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < T, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr expected_storage_base( in_place_t, std::initializer_list<U> il, Args && ... args ) : m_val( il, std::forward<Args>( args )... ), m_has_val( true ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < E, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, Args && ... args ) : m_unexpect( std::forward<Args>( args )... ), m_has_val( false ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < E, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, std::initializer_list<U> il, Args && ... args ) : m_unexpect( il, std::forward<Args>( args )... ), m_has_val( false ) {}

            ~expected_storage_base()
            {
                if ( m_has_val )
                {
                    m_val.~T();
                }
                else
                {
                    m_unexpect.~unexpected<E>();
                }
            }

            union
            {
                T m_val;
                unexpected<E> m_unexpect;
            };
            bool m_has_val;
        };

        template <class T, class E> struct expected_storage_base<T, E, true, true>
        {
            constexpr expected_storage_base() : m_val( T{} ), m_has_val( true ) {}
            constexpr expected_storage_base( no_init_t ) : m_has_val( false ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < T, Args&& ... >::value > * = nullptr >
            constexpr expected_storage_base( in_place_t, Args && ... args ) : m_val( std::forward<Args>( args )... ), m_has_val( true ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < T, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr expected_storage_base( in_place_t, std::initializer_list<U> il, Args && ... args ) : m_val( il, std::forward<Args>( args )... ), m_has_val( true ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < E, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, Args && ... args ) : m_unexpect( std::forward<Args>( args )... ), m_has_val( false ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < E, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, std::initializer_list<U> il, Args && ... args ) : m_unexpect( il, std::forward<Args>( args )... ), m_has_val( false ) {}

            ~expected_storage_base() = default;
            union
            {
                T m_val;
                unexpected<E> m_unexpect;
            };
            bool m_has_val;
        };


        template <class T, class E> struct expected_storage_base<T, E, true, false>
        {
            constexpr expected_storage_base() : m_val( T{} ), m_has_val( true ) {}
            constexpr expected_storage_base( no_init_t ) : m_has_val( false ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < T, Args&& ... >::value > * = nullptr >
            constexpr expected_storage_base( in_place_t, Args && ... args ) : m_val( std::forward<Args>( args )... ), m_has_val( true ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < T, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr expected_storage_base( in_place_t, std::initializer_list<U> il, Args && ... args ) : m_val( il, std::forward<Args>( args )... ), m_has_val( true ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < E, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, Args && ... args ) : m_unexpect( std::forward<Args>( args )... ), m_has_val( false ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < E, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, std::initializer_list<U> il, Args && ... args ) : m_unexpect( il, std::forward<Args>( args )... ), m_has_val( false ) {}

            ~expected_storage_base()
            {
                if ( !m_has_val )
                {
                    m_unexpect.~unexpected<E>();
                }
            }

            union
            {
                T m_val;
                unexpected<E> m_unexpect;
            };
            bool m_has_val;
        };


        template <class T, class E> struct expected_storage_base<T, E, false, true>
        {
            constexpr expected_storage_base() : m_val( T{} ), m_has_val( true ) {}
            constexpr expected_storage_base( no_init_t ) : m_has_val( false ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < T, Args&& ... >::value > * = nullptr >
            constexpr expected_storage_base( in_place_t, Args && ... args ) : m_val( std::forward<Args>( args )... ), m_has_val( true ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < T, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr expected_storage_base( in_place_t, std::initializer_list<U> il, Args && ... args ) : m_val( il, std::forward<Args>( args )... ), m_has_val( true ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < E, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, Args && ... args ) : m_unexpect( std::forward<Args>( args )... ), m_has_val( false ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < E, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, std::initializer_list<U> il, Args && ... args ) : m_unexpect( il, std::forward<Args>( args )... ), m_has_val( false ) {}

            ~expected_storage_base()
            {
                if ( m_has_val )
                {
                    m_val.~T();
                }
            }
            union
            {
                T m_val;
                unexpected<E> m_unexpect;
            };
            bool m_has_val;
        };

        template <class E> struct expected_storage_base<void, E, false, true>
        {
            constexpr expected_storage_base() : m_has_val( true ) {}
            constexpr expected_storage_base( no_init_t ) : m_has_val( false ) {}

            constexpr expected_storage_base( in_place_t ) : m_has_val( true ) {}

            template < class... Args, detail::enable_if_t < std::is_constructible < E, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, Args && ... args ) : m_unexpect( std::forward<Args>( args )... ), m_has_val( false ) {}

            template < class U, class... Args, detail::enable_if_t < std::is_constructible < E, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t, std::initializer_list<U> il, Args && ... args ) : m_unexpect( il, std::forward<Args>( args )... ), m_has_val( false ) {}

            ~expected_storage_base() = default;
            struct dummy {};
            union
            {
                dummy m_val;
                unexpected<E> m_unexpect;
            };
            bool m_has_val;
        };


        template <class E> struct expected_storage_base<void, E, false, false>
        {
            constexpr expected_storage_base() : m_has_val( true ) {}
            constexpr expected_storage_base( no_init_t ) : m_has_val( false ) {}

            constexpr expected_storage_base( in_place_t ) : m_has_val( true ) {}

            template < class... Args,
                       detail::enable_if_t < std::is_constructible < E, Args&& ... >::value > * =
                       nullptr >
            constexpr explicit expected_storage_base( unexpect_t, Args && ... args )
                : m_unexpect( std::forward<Args>( args )... ), m_has_val( false ) {}

            template < class U, class... Args,
                       detail::enable_if_t < std::is_constructible <
                                                 E, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
            constexpr explicit expected_storage_base( unexpect_t,
                    std::initializer_list<U> il,
                    Args && ... args )
                : m_unexpect( il, std::forward<Args>( args )... ), m_has_val( false ) {}

            ~expected_storage_base()
            {
                if ( !m_has_val )
                {
                    m_unexpect.~unexpected<E>();
                }
            }

            struct dummy {};
            union
            {
                dummy m_val;
                unexpected<E> m_unexpect;
            };
            bool m_has_val;
        };



        template <class T, class E>
    struct expected_operations_base : expected_storage_base<T, E>
        {
            using expected_storage_base<T, E>::expected_storage_base;

            template <class... Args> void construct( Args&& ... args ) noexcept
            {
                new ( std::addressof( this->m_val ) ) T( std::forward<Args>( args )... );
                this->m_has_val = true;
            }

            template <class Rhs>
            void construct_with( Rhs&& rhs ) noexcept
            {
                new ( std::addressof( this->m_val ) ) T( std::forward<Rhs>( rhs ).get() );
                this->m_has_val = true;
            }

            template <class... Args> void construct_error( Args&& ... args ) noexcept
            {
                new ( std::addressof( this->m_unexpect ) )
                unexpected<E>( std::forward<Args>( args )... );
                this->m_has_val = false;
            }







            template <class U = T,
                      detail::enable_if_t<std::is_nothrow_copy_constructible<U>::value>
                      * = nullptr>
            void assign( const expected_operations_base& rhs ) noexcept
            {
                if ( !this->m_has_val && rhs.m_has_val )
                {
                    geterr().~unexpected<E>();
                    construct( rhs.get() );
                }
                else
                {
                    assign_common( rhs );
                }
            }



            template < class U = T,
                       detail::enable_if_t < !std::is_nothrow_copy_constructible<U>::value &&
                                             std::is_nothrow_move_constructible<U>::value >
                       * = nullptr >
            void assign( const expected_operations_base& rhs ) noexcept
            {
                if ( !this->m_has_val && rhs.m_has_val )
                {
                    T tmp = rhs.get();
                    geterr().~unexpected<E>();
                    construct( std::move( tmp ) );
                }
                else
                {
                    assign_common( rhs );
                }
            }






            template < class U = T,
                       detail::enable_if_t < !std::is_nothrow_copy_constructible<U>::value &&
                                             !std::is_nothrow_move_constructible<U>::value >
                       * = nullptr >
            void assign( const expected_operations_base& rhs )
            {
                if ( !this->m_has_val && rhs.m_has_val )
                {
                    auto tmp = std::move( geterr() );
                    geterr().~unexpected<E>();

                    try
                    {
                        construct( rhs.get() );
                    }
                    catch ( ... )
                    {
                        geterr() = std::move( tmp );
                        throw;
                    }
                }
                else
                {
                    assign_common( rhs );
                }
            }


            template <class U = T,
                      detail::enable_if_t<std::is_nothrow_move_constructible<U>::value>
                      * = nullptr>
            void assign( expected_operations_base && rhs ) noexcept
            {
                if ( !this->m_has_val && rhs.m_has_val )
                {
                    geterr().~unexpected<E>();
                    construct( std::move( rhs ).get() );
                }
                else
                {
                    assign_common( rhs );
                }
            }

            template < class U = T,
                       detail::enable_if_t < !std::is_nothrow_move_constructible<U>::value >
                       * = nullptr >
            void assign( expected_operations_base && rhs )
            {
                if ( !this->m_has_val && rhs.m_has_val )
                {
                    auto tmp = std::move( geterr() );
                    geterr().~unexpected<E>();

                    try
                    {
                        construct( std::move( rhs ).get() );
                    }
                    catch ( ... )
                    {
                        geterr() = std::move( tmp );
                        throw;
                    }
                }
                else
                {
                    assign_common( rhs );
                }
            }


            template <class Rhs> void assign_common( Rhs&& rhs )
            {
                if ( this->m_has_val )
                {
                    if ( rhs.m_has_val )
                    {
                        get() = std::forward<Rhs>( rhs ).get();
                    }
                    else
                    {
                        get().~T();
                        construct_error( std::forward<Rhs>( rhs ).geterr() );
                    }
                }
                else
                {
                    if ( !rhs.m_has_val )
                    {
                        geterr() = std::forward<Rhs>( rhs ).geterr();
                    }
                }
            }

            bool has_value() const
            {
                return this->m_has_val;
            }

            constexpr T& get()& { return this->m_val; }
            constexpr const T& get() const&
            {
                return this->m_val;
            }
            constexpr T&& get()&& { return std::move( this->m_val ); }

            constexpr const T&& get() const&&
            {
                return std::move( this->m_val );
            }


            constexpr unexpected<E>& geterr()&
            {
                return this->m_unexpect;
            }
            constexpr const unexpected<E>& geterr() const&
            {
                return this->m_unexpect;
            }
            constexpr unexpected<E>&& geterr()&&
            {
                std::move( this->m_unexpect );
            }

            constexpr const unexpected<E>&& geterr() const&&
            {
                return std::move( this->m_unexpect );
            }

        };



        template <class E>
    struct expected_operations_base<void, E> : expected_storage_base<void, E>
        {
            using expected_storage_base<void, E>::expected_storage_base;

            template <class... Args> void construct() noexcept
            {
                this->m_has_val = true;
            }



            template <class Rhs>
            void construct_with( Rhs&& ) noexcept
            {
                this->m_has_val = true;
            }

            template <class... Args> void construct_error( Args&& ... args ) noexcept
            {
                new ( std::addressof( this->m_unexpect ) )
                unexpected<E>( std::forward<Args>( args )... );
                this->m_has_val = false;
            }

            template <class Rhs>
            void assign( Rhs&& rhs ) noexcept
            {
                if ( !this->m_has_val )
                {
                    if ( rhs.m_has_val )
                    {
                        geterr().~unexpected<E>();
                        construct();
                    }
                    else
                    {
                        geterr() = std::forward<Rhs>( rhs ).geterr();
                    }
                }
                else
                {
                    if ( !rhs.m_has_val )
                    {
                        construct_error( std::forward<Rhs>( rhs ).geterr() );
                    }
                }
            }

            bool has_value() const
            {
                return this->m_has_val;
            }

            constexpr unexpected<E>& geterr()&
            {
                return this->m_unexpect;
            }
            constexpr const unexpected<E>& geterr() const&
            {
                return this->m_unexpect;
            }
            constexpr unexpected<E>&& geterr()&&
            {
                std::move( this->m_unexpect );
            }

            constexpr const unexpected<E>&& geterr() const&&
            {
                return std::move( this->m_unexpect );
            }

        };



        template < class T, class E,
                   bool = is_void_or<T, std::is_trivially_copy_constructible<T>>::value &&
                   std::is_trivially_copy_constructible<E>::value >
    struct expected_copy_base : expected_operations_base<T, E>
        {
            using expected_operations_base<T, E>::expected_operations_base;
        };


        template <class T, class E>
    struct expected_copy_base<T, E, false> : expected_operations_base<T, E>
        {
            using expected_operations_base<T, E>::expected_operations_base;

            expected_copy_base() = default;
            expected_copy_base( const expected_copy_base& rhs )
                : expected_operations_base<T, E>( no_init )
            {
                if ( rhs.has_value() )
                {
                    this->construct_with( rhs );
                }
                else
                {
                    this->construct_error( rhs.geterr() );
                }
            }

            expected_copy_base( expected_copy_base&& rhs ) = default;
            expected_copy_base& operator=( const expected_copy_base& rhs ) = default;
            expected_copy_base& operator=( expected_copy_base&& rhs ) = default;
        };







        template < class T, class E,
                   bool = is_void_or<T, std::is_trivially_move_constructible<T>>::value
                   && std::is_trivially_move_constructible<E>::value >
    struct expected_move_base : expected_copy_base<T, E>
        {
            using expected_copy_base<T, E>::expected_copy_base;
        };



        template <class T, class E>
    struct expected_move_base<T, E, false> : expected_copy_base<T, E>
        {
            using expected_copy_base<T, E>::expected_copy_base;

            expected_move_base() = default;
            expected_move_base( const expected_move_base& rhs ) = default;

            expected_move_base( expected_move_base&& rhs ) noexcept(
                std::is_nothrow_move_constructible<T>::value )
                : expected_copy_base<T, E>( no_init )
            {
                if ( rhs.has_value() )
                {
                    this->construct_with( std::move( rhs ) );
                }
                else
                {
                    this->construct_error( std::move( rhs.geterr() ) );
                }
            }
            expected_move_base& operator=( const expected_move_base& rhs ) = default;
            expected_move_base& operator=( expected_move_base&& rhs ) = default;
        };


        template <
            class T, class E,
            bool = is_void_or<T,
                              conjunction<std::is_trivially_copy_assignable<T>,
                                          std::is_trivially_copy_constructible<T>,
                                          std::is_trivially_destructible<T>>>::value &&
                                          std::is_trivially_copy_assignable<E>::value &&
                                          std::is_trivially_copy_constructible<E>::value && std::is_trivially_destructible<E>::value >
                          struct expected_copy_assign_base : expected_move_base<T, E>
        {
            using expected_move_base<T, E>::expected_move_base;
        };

        template <class T, class E>
    struct expected_copy_assign_base<T, E, false> : expected_move_base<T, E>
        {
            using expected_move_base<T, E>::expected_move_base;

            expected_copy_assign_base() = default;
            expected_copy_assign_base( const expected_copy_assign_base& rhs ) = default;

            expected_copy_assign_base( expected_copy_assign_base&& rhs ) = default;
            expected_copy_assign_base& operator=( const expected_copy_assign_base& rhs )
            {
                this->assign( rhs );
                return *this;
            }
            expected_copy_assign_base&
            operator=( expected_copy_assign_base&& rhs ) = default;
        };







        template < class T, class E,
                   bool =
                   is_void_or<T, conjunction<std::is_trivially_destructible<T>,
                                             std::is_trivially_move_constructible<T>,
                                             std::is_trivially_move_assignable<T>>>::value
                                             && std::is_trivially_destructible<E>::value
                                             && std::is_trivially_move_constructible<E>::value
                                             && std::is_trivially_move_assignable<E>::value >
                          struct expected_move_assign_base : expected_copy_assign_base<T, E>
        {
            using expected_copy_assign_base<T, E>::expected_copy_assign_base;
        };




        template <class T, class E>
        struct expected_move_assign_base<T, E, false>
    : expected_copy_assign_base<T, E>
        {
            using expected_copy_assign_base<T, E>::expected_copy_assign_base;

            expected_move_assign_base() = default;
            expected_move_assign_base( const expected_move_assign_base& rhs ) = default;

            expected_move_assign_base( expected_move_assign_base&& rhs ) = default;

            expected_move_assign_base&
            operator=( const expected_move_assign_base& rhs ) = default;

            expected_move_assign_base&
            operator=( expected_move_assign_base&& rhs ) noexcept(
                std::is_nothrow_move_constructible<T>::value
                && std::is_nothrow_move_assignable<T>::value )
            {
                this->assign( std::move( rhs ) );
                return *this;
            }
        };



        template < class T, class E,
                   bool EnableCopy = ( is_copy_constructible_or_void<T>::value &&
                                       std::is_copy_constructible<E>::value ),
                   bool EnableMove = ( is_move_constructible_or_void<T>::value &&
                                       std::is_move_constructible<E>::value ) >
        struct expected_delete_ctor_base
        {
            expected_delete_ctor_base() = default;
            expected_delete_ctor_base( const expected_delete_ctor_base& ) = default;
            expected_delete_ctor_base( expected_delete_ctor_base&& ) noexcept = default;
            expected_delete_ctor_base&
            operator=( const expected_delete_ctor_base& ) = default;
            expected_delete_ctor_base&
            operator=( expected_delete_ctor_base&& ) noexcept = default;
        };

        template <class T, class E>
        struct expected_delete_ctor_base<T, E, true, false>
        {
            expected_delete_ctor_base() = default;
            expected_delete_ctor_base( const expected_delete_ctor_base& ) = default;
            expected_delete_ctor_base( expected_delete_ctor_base&& ) noexcept = delete;
            expected_delete_ctor_base&
            operator=( const expected_delete_ctor_base& ) = default;
            expected_delete_ctor_base&
            operator=( expected_delete_ctor_base&& ) noexcept = default;
        };

        template <class T, class E>
        struct expected_delete_ctor_base<T, E, false, true>
        {
            expected_delete_ctor_base() = default;
            expected_delete_ctor_base( const expected_delete_ctor_base& ) = delete;
            expected_delete_ctor_base( expected_delete_ctor_base&& ) noexcept = default;
            expected_delete_ctor_base&
            operator=( const expected_delete_ctor_base& ) = default;
            expected_delete_ctor_base&
            operator=( expected_delete_ctor_base&& ) noexcept = default;
        };

        template <class T, class E>
        struct expected_delete_ctor_base<T, E, false, false>
        {
            expected_delete_ctor_base() = default;
            expected_delete_ctor_base( const expected_delete_ctor_base& ) = delete;
            expected_delete_ctor_base( expected_delete_ctor_base&& ) noexcept = delete;
            expected_delete_ctor_base&
            operator=( const expected_delete_ctor_base& ) = default;
            expected_delete_ctor_base&
            operator=( expected_delete_ctor_base&& ) noexcept = default;
        };




        template < class T, class E,
                   bool EnableCopy = ( std::is_copy_constructible<T>::value &&
                                       std::is_copy_constructible<E>::value &&
                                       std::is_copy_assignable<T>::value &&
                                       std::is_copy_assignable<E>::value ),
                   bool EnableMove = ( std::is_move_constructible<T>::value &&
                                       std::is_move_constructible<E>::value &&
                                       std::is_move_assignable<T>::value &&
                                       std::is_move_assignable<E>::value ) >
        struct expected_delete_assign_base
        {
            expected_delete_assign_base() = default;
            expected_delete_assign_base( const expected_delete_assign_base& ) = default;
            expected_delete_assign_base( expected_delete_assign_base&& ) noexcept =
                default;
            expected_delete_assign_base&
            operator=( const expected_delete_assign_base& ) = default;
            expected_delete_assign_base&
            operator=( expected_delete_assign_base&& ) noexcept = default;
        };

        template <class T, class E>
        struct expected_delete_assign_base<T, E, true, false>
        {
            expected_delete_assign_base() = default;
            expected_delete_assign_base( const expected_delete_assign_base& ) = default;
            expected_delete_assign_base( expected_delete_assign_base&& ) noexcept =
                default;
            expected_delete_assign_base&
            operator=( const expected_delete_assign_base& ) = default;
            expected_delete_assign_base&
            operator=( expected_delete_assign_base&& ) noexcept = delete;
        };

        template <class T, class E>
        struct expected_delete_assign_base<T, E, false, true>
        {
            expected_delete_assign_base() = default;
            expected_delete_assign_base( const expected_delete_assign_base& ) = default;
            expected_delete_assign_base( expected_delete_assign_base&& ) noexcept =
                default;
            expected_delete_assign_base&
            operator=( const expected_delete_assign_base& ) = delete;
            expected_delete_assign_base&
            operator=( expected_delete_assign_base&& ) noexcept = default;
        };

        template <class T, class E>
        struct expected_delete_assign_base<T, E, false, false>
        {
            expected_delete_assign_base() = default;
            expected_delete_assign_base( const expected_delete_assign_base& ) = default;
            expected_delete_assign_base( expected_delete_assign_base&& ) noexcept =
                default;
            expected_delete_assign_base&
            operator=( const expected_delete_assign_base& ) = delete;
            expected_delete_assign_base&
            operator=( expected_delete_assign_base&& ) noexcept = delete;
        };



        struct default_constructor_tag
        {
            explicit constexpr default_constructor_tag() = default;
        };




        template < class T, class E,
                   bool Enable = std::is_default_constructible<T>::value || std::is_void<T>::value >
        struct expected_default_ctor_base
        {
            constexpr expected_default_ctor_base() noexcept = default;
            constexpr expected_default_ctor_base(
                expected_default_ctor_base const& ) noexcept = default;
            constexpr expected_default_ctor_base( expected_default_ctor_base&& ) noexcept =
                default;
            expected_default_ctor_base&
            operator=( expected_default_ctor_base const& ) noexcept = default;
            expected_default_ctor_base&
            operator=( expected_default_ctor_base&& ) noexcept = default;

            constexpr explicit expected_default_ctor_base( default_constructor_tag ) {}
        };


        template <class T, class E> struct expected_default_ctor_base<T, E, false>
        {
            constexpr expected_default_ctor_base() noexcept = delete;
            constexpr expected_default_ctor_base(
                expected_default_ctor_base const& ) noexcept = default;
            constexpr expected_default_ctor_base( expected_default_ctor_base&& ) noexcept =
                default;
            expected_default_ctor_base&
            operator=( expected_default_ctor_base const& ) noexcept = default;
            expected_default_ctor_base&
            operator=( expected_default_ctor_base&& ) noexcept = default;

            constexpr explicit expected_default_ctor_base( default_constructor_tag ) {}
        };
    }

template <class E> class bad_expected_access : public std::exception
    {
    public:
        explicit bad_expected_access( E e ) : m_val( std::move( e ) ) {}

        virtual const char* what() const noexcept override
        {
            return "Bad expected access";
        }

        const E& error() const&
        {
            return m_val;
        }
        E& error()& { return m_val; }
        const E&& error() const&&
        {
            return std::move( m_val );
        }
        E&& error()&& { return std::move( m_val ); }

    private:
        E m_val;
    };
    // 1045 "././expected.hpp"
    template <class T, class E>
class expected : private detail::expected_move_assign_base<T, E>,
    private detail::expected_delete_ctor_base<T, E>,
    private detail::expected_delete_assign_base<T, E>,
    private detail::expected_default_ctor_base<T, E>
    {
        static_assert( !std::is_reference<T>::value, "T must not be a reference" );
        static_assert( !std::is_same<T, std::remove_cv<in_place_t>>::value,
                       "T must not be in_place_t" );
        static_assert( !std::is_same<T, std::remove_cv<unexpect_t>>::value,
                       "T must not be unexpect_t" );
        static_assert( !std::is_same<T, std::remove_cv<unexpected<E>>>::value,
                       "T must not be unexpected<E>" );
        static_assert( !std::is_reference<E>::value, "E must not be a reference" );

        T* valptr()
        {
            return std::addressof( this->m_val );
        }
        unexpected<E>* errptr()
        {
            return std::addressof( this->m_unexpect );
        }

        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        U & val()
        {
            return this->m_val;
        }
        unexpected<E>& err()
        {
            return this->m_unexpect;
        }

        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        const U & val() const
        {
            return this->m_val;
        }
        const unexpected<E>& err() const
        {
            return this->m_unexpect;
        }

        using impl_base = detail::expected_move_assign_base<T, E>;
        using ctor_base = detail::expected_default_ctor_base<T, E>;

    public:
        typedef T value_type;
        typedef E error_type;
        typedef unexpected<E> unexpected_type;
        // 1089 "././expected.hpp"
        template <class F> constexpr auto and_then( F&& f )&
        {
            return and_then_impl( *this, std::forward<F>( f ) );
                                }



        template <class F> constexpr auto and_then( F&& f )&&
        {
            return and_then_impl( std::move( *this ), std::forward<F>( f ) );
                                }



        template <class F> constexpr auto and_then( F&& f ) const&
        {
            return and_then_impl( *this, std::forward<F>( f ) );
        }




        template <class F> constexpr auto and_then( F&& f ) const&&
        {
            return and_then_impl( std::move( *this ), std::forward<F>( f ) );
        }
        // 1164 "././expected.hpp"
        template <class F> constexpr auto map( F&& f )&
        {
            return map_impl( *this, std::forward<F>( f ) );
                           }



        template <class F> constexpr auto map( F&& f )&&
        {
            return map_impl( std::move( *this ), std::forward<F>( f ) );
                           }



        template <class F> constexpr auto map( F&& f ) const&
        {
            return map_impl( *this, std::forward<F>( f ) );
        }



        template <class F> constexpr auto map( F&& f ) const&&
        {
            return map_impl( std::move( *this ), std::forward<F>( f ) );
        }
        // 1246 "././expected.hpp"
        template <class F> constexpr auto map_error( F&& f )&
        {
            return map_error_impl( *this, std::forward<F>( f ) );
                                 }



        template <class F> constexpr auto map_error( F&& f )&&
        {
            return map_error_impl( std::move( *this ), std::forward<F>( f ) );
                                 }



        template <class F> constexpr auto map_error( F&& f ) const&
        {
            return map_error_impl( *this, std::forward<F>( f ) );
        }



        template <class F> constexpr auto map_error( F&& f ) const&&
        {
            return map_error_impl( std::move( *this ), std::forward<F>( f ) );
        }
        // 1323 "././expected.hpp"
        template <class F> expected constexpr or_else( F&& f )&
        {
            return or_else_impl( *this, std::forward<F>( f ) );
        }

        template <class F> expected constexpr or_else( F&& f )&&
        {
            return or_else_impl( std::move( *this ), std::forward<F>( f ) );
        }

        template <class F> expected constexpr or_else( F&& f ) const&
        {
            return or_else_impl( *this, std::forward<F>( f ) );
        }

        template <class F> expected constexpr or_else( F&& f ) const&&
        {
            return or_else_impl( std::move( *this ), std::forward<F>( f ) );
        }

        constexpr expected() = default;
        constexpr expected( const expected& rhs ) = default;
        constexpr expected( expected&& rhs ) = default;
        expected& operator=( const expected& rhs ) = default;
        expected& operator=( expected&& rhs ) = default;

        template < class... Args,
                   detail::enable_if_t < std::is_constructible < T, Args&& ... >::value > * =
                   nullptr >
        constexpr expected( in_place_t, Args && ... args )
            : impl_base( in_place, std::forward<Args>( args )... ),
              ctor_base( detail::default_constructor_tag{} ) {}

        template < class U, class... Args,
                   detail::enable_if_t < std::is_constructible <
                                             T, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
        constexpr expected( in_place_t, std::initializer_list<U> il, Args && ... args )
            : impl_base( in_place, il, std::forward<Args>( args )... ),
              ctor_base( detail::default_constructor_tag {} ) {}



        template < class G = E,
                   detail::enable_if_t<std::is_constructible<E, const G&>::value>* =
                   nullptr,
                   detail::enable_if_t < !std::is_convertible<const G&, E>::value > * =
                   nullptr >
        explicit constexpr expected( const unexpected<G>& e )
            : impl_base( unexpect, e.value() ),
              ctor_base( detail::default_constructor_tag {} ) {}


        template <
            class G = E,
            detail::enable_if_t<std::is_constructible<E, const G&>::value>* =
            nullptr,
            detail::enable_if_t<std::is_convertible<const G&, E>::value>* = nullptr >
        constexpr expected( unexpected<G> const& e )
            : impl_base( unexpect, e.value() ),
              ctor_base( detail::default_constructor_tag {} ) {}



        template <
            class G = E,
            detail::enable_if_t < std::is_constructible < E, G && >::value > * = nullptr,
            detail::enable_if_t < !std::is_convertible < G &&, E >::value > * = nullptr >
        explicit constexpr expected( unexpected<G>&& e ) noexcept(
            std::is_nothrow_constructible < E, G && >::value )
            : impl_base( unexpect, std::move( e.value() ) ),
              ctor_base( detail::default_constructor_tag {} ) {}


        template <
            class G = E,
            detail::enable_if_t < std::is_constructible < E, G && >::value > * = nullptr,
            detail::enable_if_t < std::is_convertible < G &&, E >::value > * = nullptr >
        constexpr expected( unexpected<G>&& e ) noexcept(
            std::is_nothrow_constructible < E, G && >::value )
            : impl_base( unexpect, std::move( e.value() ) ),
              ctor_base( detail::default_constructor_tag {} ) {}

        template < class... Args,
                   detail::enable_if_t < std::is_constructible < E, Args&& ... >::value > * =
                   nullptr >
        constexpr explicit expected( unexpect_t, Args && ... args )
            : impl_base( unexpect, std::forward<Args>( args )... ),
              ctor_base( detail::default_constructor_tag{} ) {}


        template < class U, class... Args,
                   detail::enable_if_t < std::is_constructible <
                                             E, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
        constexpr explicit expected( unexpect_t, std::initializer_list<U> il,
                                     Args && ... args )
            : impl_base( unexpect, il, std::forward<Args>( args )... ),
              ctor_base( detail::default_constructor_tag {} ) {}

        template < class U, class G,
                   detail::enable_if_t < !( std::is_convertible<U const&, T>::value&&
                                            std::is_convertible<G const&, E>::value ) > * =
                   nullptr,
                   detail::expected_enable_from_other<T, E, U, G, const U&, const G&>
                   * = nullptr >
        explicit constexpr expected( const expected<U, G>& rhs )
            : ctor_base( detail::default_constructor_tag {} )
        {
            if ( rhs.has_value() )
            {
                ::new ( valptr() ) T( *rhs );
            }
            else
            {
                ::new ( errptr() ) unexpected_type( unexpected<E>( rhs.error() ) );
            }
        }


        template < class U, class G,
                   detail::enable_if_t < ( std::is_convertible<U const&, T>::value&&
                                           std::is_convertible<G const&, E>::value ) > * =
                   nullptr,
                   detail::expected_enable_from_other<T, E, U, G, const U&, const G&>
                   * = nullptr >
        constexpr expected( const expected<U, G>& rhs )
            : ctor_base( detail::default_constructor_tag {} )
        {
            if ( rhs.has_value() )
            {
                ::new ( valptr() ) T( *rhs );
            }
            else
            {
                ::new ( errptr() ) unexpected_type( unexpected<E>( rhs.error() ) );
            }
        }

        template <
            class U, class G,
            detail::enable_if_t < !( std::is_convertible < U&&, T >::value&&
                                     std::is_convertible < G&&, E >::value ) > * = nullptr,
            detail::expected_enable_from_other < T, E, U, G, U &&, G && > * = nullptr >
        explicit constexpr expected( expected<U, G>&& rhs )
            : ctor_base( detail::default_constructor_tag {} )
        {
            if ( rhs.has_value() )
            {
                ::new ( valptr() ) T( std::move( *rhs ) );
            }
            else
            {
                ::new ( errptr() ) unexpected_type( unexpected<E>( std::move( rhs.error() ) ) );
            }
        }


        template <
            class U, class G,
            detail::enable_if_t < ( std::is_convertible < U&&, T >::value&&
                                    std::is_convertible < G&&, E >::value ) > * = nullptr,
            detail::expected_enable_from_other < T, E, U, G, U &&, G && > * = nullptr >
        constexpr expected( expected<U, G>&& rhs )
            : ctor_base( detail::default_constructor_tag {} )
        {
            if ( rhs.has_value() )
            {
                ::new ( valptr() ) T( std::move( *rhs ) );
            }
            else
            {
                ::new ( errptr() ) unexpected_type( unexpected<E>( std::move( rhs.error() ) ) );
            }
        }

        template <
            class U = T,
            detail::enable_if_t < !std::is_convertible < U &&, T >::value > * = nullptr,
            detail::expected_enable_forward_value<T, E, U>* = nullptr >
        explicit constexpr expected( U && v ) : expected( in_place, std::forward<U>( v ) ) {}


        template <
            class U = T,
            detail::enable_if_t < std::is_convertible < U &&, T >::value > * = nullptr,
            detail::expected_enable_forward_value<T, E, U>* = nullptr >
        constexpr expected( U && v ) : expected( in_place, std::forward<U>( v ) ) {}

        template <
            class U = T,
            class G = T,
            detail::enable_if_t < std::is_nothrow_constructible < T, U && >::value > * =
            nullptr,
            detail::enable_if_t < !std::is_void<G>::value > * = nullptr,
            detail::enable_if_t <
                ( !std::is_same<expected<T, E>, detail::decay_t<U>>::value &&
                  !detail::conjunction<std::is_scalar<T>,
                                       std::is_same<T, detail::decay_t<U>>>::value &&
                                               std::is_constructible<T, U>::value &&
                                               std::is_assignable<G&, U>::value &&
                                               std::is_nothrow_move_constructible<E>::value ) > * = nullptr
                  >
                expected & operator=( U && v )
        {
            if ( has_value() )
            {
                val() = std::forward<U>( v );
            }
            else
            {
                err().~unexpected<E>();
                ::new ( valptr() ) T( std::forward<U>( v ) );
                this->m_has_val = true;
            }

            return *this;
        }


        template <
            class U = T,
            class G = T,
            detail::enable_if_t < !std::is_nothrow_constructible < T, U && >::value > * =
            nullptr,
            detail::enable_if_t < !std::is_void<U>::value > * = nullptr,
            detail::enable_if_t <
                ( !std::is_same<expected<T, E>, detail::decay_t<U>>::value &&
                  !detail::conjunction<std::is_scalar<T>,
                                       std::is_same<T, detail::decay_t<U>>>::value &&
                                               std::is_constructible<T, U>::value &&
                                               std::is_assignable<G&, U>::value &&
                                               std::is_nothrow_move_constructible<E>::value ) > * = nullptr
                  >
                expected & operator=( U && v )
        {
            if ( has_value() )
            {
                val() = std::forward<U>( v );
            }
            else
            {
                auto tmp = std::move( err() );
                err().~unexpected<E>();

                try
                {
                    ::new ( valptr() ) T( std::move( v ) );
                    this->m_has_val = true;
                }
                catch ( ... )
                {
                    err() = std::move( tmp );
                    throw;
                }
            }

            return *this;
        }

        template < class G = E,
                   detail::enable_if_t < std::is_nothrow_copy_constructible<G>::value &&
                                         std::is_assignable<G&, G>::value > * = nullptr >
        expected & operator=( const unexpected<G>& rhs )
        {
            if ( !has_value() )
            {
                err() = rhs;
            }
            else
            {
                val().~T();
                ::new ( errptr() ) unexpected<E>( rhs );
                this->m_has_val = false;
            }

            return *this;
        }

        template < class G = E,
                   detail::enable_if_t < std::is_nothrow_move_constructible<G>::value &&
                                         std::is_move_assignable<G>::value > * = nullptr >
        expected & operator=( unexpected<G>&& rhs ) noexcept
        {
            if ( !has_value() )
            {
                err() = std::move( rhs );
            }
            else
            {
                val().~T();
                ::new ( errptr() ) unexpected<E>( std::move( rhs ) );
                this->m_has_val = false;
            }

            return *this;
        }

        template < class... Args, detail::enable_if_t < std::is_nothrow_constructible <
                       T, Args&& ... >::value > * = nullptr >
        void emplace( Args && ... args )
        {
            if ( has_value() )
            {
                val() = T( std::forward<Args>( args )... );
            }
            else
            {
                err().~unexpected<E>();
                ::new ( valptr() ) T( std::forward<Args>( args )... );
                this->m_has_val = true;
            }
        }


        template < class... Args, detail::enable_if_t < !std::is_nothrow_constructible <
                       T, Args&& ... >::value > * = nullptr >
        void emplace( Args && ... args )
        {
            if ( has_value() )
            {
                val() = T( std::forward<Args>( args )... );
            }
            else
            {
                auto tmp = std::move( err() );
                err().~unexpected<E>();

                try
                {
                    ::new ( valptr() ) T( std::forward<Args>( args )... );
                    this->m_has_val = true;
                }
                catch ( ... )
                {
                    err() = std::move( tmp );
                    throw;
                }
            }
        }

        template < class U, class... Args,
                   detail::enable_if_t < std::is_nothrow_constructible <
                                             T, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
        void emplace( std::initializer_list<U> il, Args && ... args )
        {
            if ( has_value() )
            {
                T t( il, std::forward<Args>( args )... );
                val() = std::move( t );
            }
            else
            {
                err().~unexpected<E>();
                ::new ( valptr() ) T( il, std::forward<Args>( args )... );
                this->m_has_val = true;
            }
        }


        template < class U, class... Args,
                   detail::enable_if_t < !std::is_nothrow_constructible <
                                             T, std::initializer_list<U>&, Args&& ... >::value > * = nullptr >
        void emplace( std::initializer_list<U> il, Args && ... args )
        {
            if ( has_value() )
            {
                T t( il, std::forward<Args>( args )... );
                val() = std::move( t );
            }
            else
            {
                auto tmp = std::move( err() );
                err().~unexpected<E>();

                try
                {
                    ::new ( valptr() ) T( il, std::forward<Args>( args )... );
                    this->m_has_val = true;
                }
                catch ( ... )
                {
                    err() = std::move( tmp );
                    throw;
                }
            }
        }


        void swap( expected& rhs ) noexcept(
            std::is_nothrow_move_constructible<T>::value&& noexcept(
                swap( std::declval<T&>(), std::declval<T&>() ) )&&
            std::is_nothrow_move_constructible<E>::value&&
            noexcept( swap( std::declval<E&>(), std::declval<E&>() ) ) )
        {
            if ( has_value() && rhs.has_value() )
            {
                using std::swap;
                swap( val(), rhs.val() );
            }
            else if ( !has_value() && rhs.has_value() )
            {
                using std::swap;
                swap( err(), rhs.err() );
            }
            else if ( has_value() )
            {
                auto temp = std::move( rhs.err() );
                ::new ( rhs.valptr() ) T( val() );
                ::new ( errptr() ) unexpected_type( std::move( temp ) );
                std::swap( this->m_has_val, rhs.m_has_val );
            }
            else
            {
                auto temp = std::move( this->err() );
                ::new ( valptr() ) T( rhs.val() );
                ::new ( errptr() ) unexpected_type( std::move( temp ) );
                std::swap( this->m_has_val, rhs.m_has_val );
            }
        }




        constexpr const T* operator->() const
        {
            return valptr();
        }

        constexpr T* operator->()
        {
            return valptr();
        }




        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        constexpr const U & operator*() const&
        {
            return val();
        }

        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        constexpr U & operator*()&
        {
            return val();
        }

        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        constexpr const U && operator*() const &&
        {
            return std::move( val() );
        }

        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        constexpr U && operator*() &&
        {
            return std::move( val() );
        }



        constexpr bool has_value() const noexcept
        {
            return this->m_has_val;
        }

        constexpr explicit operator bool() const noexcept
        {
            return this->m_has_val;
        }





        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        constexpr const U & value() const&
        {
            if ( !has_value() )
                throw bad_expected_access<E>( err().value() );

            return val();
        }

        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        constexpr U & value()&
        {
            if ( !has_value() )
            throw bad_expected_access<E>( err().value() );

            return val();
                                     }

        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        constexpr const U && value() const &&
        {
            if ( !has_value() )
                throw bad_expected_access<E>( err().value() );

            return std::move( val() );
        }

        template < class U = T, detail::enable_if_t < !std::is_void<U>::value > * = nullptr >
        constexpr U && value() &&
        {
            if ( !has_value() )
            throw bad_expected_access<E>( err().value() );

            return std::move( val() );
                                     }




        constexpr const E& error() const&
        {
            return err().value();
        }

        constexpr E& error()& { return err().value(); }

        constexpr const E&& error() const&&
        {
            return std::move( err().value() );
        }

        constexpr E&& error()&& { return std::move( err().value() ); }



        template <class U> constexpr T value_or( U&& v ) const&
        {
            static_assert( std::is_copy_constructible<T>::value &&
                           std::is_convertible < U &&, T >::value,
                           "T must be copy-constructible and convertible to from U&&" );
            return bool( *this ) ? **this : static_cast<T>( std::forward<U>( v ) );
        }

        template <class U> constexpr T value_or( U&& v )&&
        {
            static_assert( std::is_move_constructible<T>::value&&
                           std::is_convertible < U&&, T >::value,
                           "T must be move-constructible and convertible to from U&&" );
            return bool( *this ) ? std::move( **this ) : static_cast<T>( std::forward<U>( v ) );
        }
    };


    namespace detail
    {
        template <class Exp> using exp_t = typename detail::decay_t<Exp>::value_type;
        template <class Exp> using err_t = typename detail::decay_t<Exp>::error_type;
        template <class Exp, class Ret> using ret_t = expected<Ret, err_t<Exp>>;


        template < class Exp, class F,
                   class Ret = decltype( detail::invoke( std::declval<F>(),
                                         *std::declval<Exp>() ) ),
                   detail::enable_if_t < !std::is_void<exp_t<Exp>>::value > * = nullptr >
        constexpr auto and_then_impl( Exp && exp, F && f )
        {
            static_assert( detail::is_expected<Ret>::value,
                           "F must return an expected" );
            return exp.has_value() ? detail::invoke( std::forward<F>( f ), *std::forward<Exp>( exp ) )
                   : Ret( unexpect, exp.error() );
        }

        template <class Exp, class F,
                  class Ret = decltype( detail::invoke( std::declval<F>(),
                                        *std::declval<Exp>() ) ),
                  detail::enable_if_t<std::is_void<exp_t<Exp>>::value> * = nullptr>
        constexpr auto and_then_impl( Exp && exp, F && f )
        {
            static_assert( detail::is_expected<Ret>::value,
                           "F must return an expected" );
            return exp.has_value() ? detail::invoke( std::forward<F>( f ) )
                   : Ret( unexpect, exp.error() );
        }
        // 1818 "././expected.hpp"
        template < class Exp, class F,
                   class Ret = decltype( detail::invoke( std::declval<F>(),
                                         *std::declval<Exp>() ) ),
                   detail::enable_if_t < !std::is_void<Ret>::value > * = nullptr >
        constexpr auto map_impl( Exp && exp, F && f )
        {
            using result = ret_t<Exp, detail::decay_t<Ret>>;
            return exp.has_value() ? result( detail::invoke( std::forward<F>( f ),
                                             *std::forward<Exp>( exp ) ) )
                   : result( unexpect, std::forward<Exp>( exp ).error() );
        }

        template <class Exp, class F,
                  class Ret = decltype( detail::invoke( std::declval<F>(),
                                        *std::declval<Exp>() ) ),
                  detail::enable_if_t<std::is_void<Ret>::value> * = nullptr>
        auto map_impl( Exp && exp, F && f )
        {
            using result = expected<void, err_t<Exp>>;

            if ( exp.has_value() )
            {
                detail::invoke( std::forward<F>( f ), *std::forward<Exp>( exp ) );
                return result();
            }

            return result( unexpect, std::forward<Exp>( exp ).error() );
        }

        template < class Exp, class F,
                   class Ret = decltype( detail::invoke( std::declval<F>(),
                                         *std::declval<Exp>() ) ),
                   detail::enable_if_t < !std::is_void<Ret>::value > * = nullptr >
        constexpr auto map_error_impl( Exp && exp, F && f )
        {
            using result = expected<exp_t<Exp>, detail::decay_t<Ret>>;
            return exp.has_value()
                   ? result( *std::forward<Exp>( exp ) )
                   : result( unexpect, detail::invoke( std::forward<F>( f ),
                             std::forward<Exp>( exp ).error() ) );
        }
        template <class Exp, class F, class Ret = decltype( detail::invoke( std::declval<F>(), *std::declval<Exp>() ) ), detail::enable_if_t<std::is_void<Ret>::value> * = nullptr>
        auto map_error_impl( Exp && exp, F && f )
        {
            using result = expected<exp_t<Exp>, monostate>;

            if ( exp.has_value() )
            {
                return result( *std::forward<Exp>( exp ) );
            }

            detail::invoke( std::forward<F>( f ), std::forward<Exp>( exp ).error() );
            return result( unexpect, monostate{} );
        }

        template < class Exp, class F, class Ret = decltype( detail::invoke( std::declval<F>(), *std::declval<Exp>() ) ), detail::enable_if_t < !std::is_void<Ret>::value > * = nullptr >
        constexpr detail::decay_t<Exp> or_else_impl( Exp && exp, F && f )
        {
            if ( exp.has_value() )
            {
                return std::forward<Exp>( exp );
            }

            return detail::invoke( std::forward<F>( f ), *std::forward<Exp>( exp ) );
        }

        template <class Exp, class F, class Ret = decltype( detail::invoke( std::declval<F>(), *std::declval<Exp>() ) ), detail::enable_if_t<std::is_void<Ret>::value> * = nullptr>
        detail::decay_t<Exp> or_else_impl( Exp && exp, F && f )
        {
            if ( exp.has_value() )
            {
                return std::forward<Exp>( exp );
            }

            detail::invoke( std::forward<F>( f ), *std::forward<Exp>( exp ) );
            return std::forward<Exp>( exp );
        }

    }

    template <class T, class E, class U, class F>
    constexpr bool operator==( const expected<T, E>& lhs, const expected<U, F>& rhs )
    {
        return ( lhs.has_value() != rhs.has_value() ) ? false : ( !lhs.has_value() ? lhs.error() == rhs.error() : *lhs == *rhs );
    }
    template <class T, class E, class U, class F>
    constexpr bool operator!=( const expected<T, E>& lhs, const expected<U, F>& rhs )
    {
        return ( lhs.has_value() != rhs.has_value() ) ? true : ( !lhs.has_value() ? lhs.error() != rhs.error() : *lhs != *rhs );
    }

    template <class T, class E, class U>
    constexpr bool operator==( const expected<T, E>& x, const U& v )
    {
        return x.has_value() ? *x == v : false;
    }

    template <class T, class E, class U>
    constexpr bool operator==( const U& v, const expected<T, E>& x )
    {
        return x.has_value() ? *x == v : false;
    }

    template <class T, class E, class U>
    constexpr bool operator!=( const expected<T, E>& x, const U& v )
    {
        return x.has_value() ? *x != v : true;
    }

    template <class T, class E, class U>
    constexpr bool operator!=( const U& v, const expected<T, E>& x )
    {
        return x.has_value() ? *x != v : true;
    }

    template <class T, class E>
    constexpr bool operator==( const expected<T, E>& x, const unexpected<E>& e )
    {
        return x.has_value() ? false : x.error() == e.value();
    }

    template <class T, class E>
    constexpr bool operator==( const unexpected<E>& e, const expected<T, E>& x )
    {
        return x.has_value() ? false : x.error() == e.value();
    }

    template <class T, class E>
    constexpr bool operator!=( const expected<T, E>& x, const unexpected<E>& e )
    {
        return x.has_value() ? true : x.error() != e.value();
    }

    template <class T, class E>
    constexpr bool operator!=( const unexpected<E>& e, const expected<T, E>& x )
    {
        return x.has_value() ? true : x.error() != e.value();
    }

    template < class T, class E, detail::enable_if_t < std::is_move_constructible<T>::value&& std::is_move_constructible<E>::value > * = nullptr >
    void swap( expected<T, E>& lhs, expected<T, E>& rhs ) noexcept( noexcept( lhs.swap( rhs ) ) )
    {
        lhs.swap( rhs );
    }
}
