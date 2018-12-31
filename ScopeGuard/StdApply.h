#ifndef _STDAPPLY_H_4481593C_1515_47C1_9BD7_944B4FCE736B_
#define _STDAPPLY_H_4481593C_1515_47C1_9BD7_944B4FCE736B_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if 1

// https://stackoverflow.com/questions/34668720/stdapply-may-not-be-properly-implemented

namespace std
{
    namespace detail
    {
        template <typename F, typename Tuple, size_t... I>
        decltype(auto) apply_impl(F&& f, Tuple&& t, index_sequence<I...>)
        {
            return forward<F>(f)(get<I>(forward<Tuple>(t))...);
        }
    }

    template <typename F, typename Tuple>
    decltype(auto) apply(F&& f, Tuple&& t)
    {
        using Indices = make_index_sequence<tuple_size<decay_t<Tuple>>::value>;
        return detail::apply_impl(forward<F>(f), forward<Tuple>(t), Indices{});
    }
}

#else

// https://en.cppreference.com/w/cpp/utility/apply

namespace std
{
    namespace detail
    {
        template <class F, class Tuple, std::size_t... I>
        constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
        {
            // Note: std::invoke is a C++17 feature
            return std::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
        }
    }

    template <class F, class Tuple>
    constexpr decltype(auto) apply(F&& f, Tuple&& t)
    {
        return detail::apply_impl(
            std::forward<F>(f), std::forward<Tuple>(t),
            std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
    }
}

#endif

#endif
