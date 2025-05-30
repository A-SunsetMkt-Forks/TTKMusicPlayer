#ifndef TTKTRAITS_H
#define TTKTRAITS_H

/***************************************************************************
 * This file is part of the TTK Library Module project
 * Copyright (C) 2015 - 2025 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#if 1
#define TTK_DECLARE_HAS_MEMBER(__trait_name__) \
    template <typename T, typename... Args> \
    struct has_member_##__trait_name__ \
    { \
    private: \
        template <typename U> \
        static auto test(int)->decltype(std::declval<U>().__trait_name__(std::declval<Args>() ...), std::true_type()); \
        template <typename U> \
        static std::false_type test(...); \
    public: \
        static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value; \
    }
#else
#define TTK_DECLARE_HAS_MEMBER(__trait_name__, __member_name__) \
    template <typename T> \
    struct __trait_name__ \
    { \
        typedef typename std::remove_const<T>::type check_type; \
        struct base { void __member_name__() {}}; \
        struct mixin : public base, public check_type {}; \
        template <void (base::*)()> struct aux {}; \
        template <typename U> static std::false_type test(aux<&U::__member_name__>*); \
        template <typename U> static std::true_type test(...); \
        static constexpr bool value = (sizeof(std::true_type) == sizeof(test<mixin>(0))); \
    }
#endif

#define TTK_DECLARE_GLOBAL_SIGNATURE(__trait_name__, __func_name__) \
    std::nullptr_t __func_name__(...); \
    template <typename T> \
    struct __trait_name__ \
    { \
        template <typename U, U> struct helper; \
        template <typename U> static std::uint8_t test(helper<U*, &__func_name__>*); \
        template <typename U> static std::uint16_t test(...); \
        static constexpr bool value = sizeof(test<T>(0)) == sizeof(std::uint8_t); \
    }

#define TTK_DECLARE_CLASS_SIGNATURE(__trait_name__, __func_name__) \
    template <typename Void, typename Obj, typename Func> \
    struct __trait_name__ : std::false_type {}; \
    template <typename Obj, typename Func> \
    struct __trait_name__<std::void_t<decltype(static_cast<Func Obj::*>(&Obj::__func_name__))>, Obj, Func> : std::true_type {}; \
    template <typename Obj, typename Func> \
    using __trait_name__##Check = __trait_name__<void, Obj, Func>;

#endif // TTKTRAITS_H
