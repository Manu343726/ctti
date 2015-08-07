#pragma once

#if defined(_MSC_VER)
#error "Sorry but ctti::detail::array<T,N> is not supported by Visual Studio. MSVC doesn't implement constexpr array initialization"
#else

#include <cstdint>
#include <type_traits>

namespace ctti
{
	namespace detail
	{
		template<typename T, std::size_t Size>
		struct array;

		template<std::size_t Begin, std::size_t End, typename T>
		constexpr array<T, End - Begin> make_array(const T* const arr);

		template<typename T, std::size_t Size>
		struct array
		{
			template<std::size_t N>
			constexpr array(const T(&arr)[N]) :
				array{arr, std::make_index_sequence<N>{}}
			{}

			template<std::size_t N>
			constexpr array(const array<T,N> arr) :
				array{arr.data(), std::make_index_sequence<N>{}}
			{}

			template<typename Head, typename... Tail, typename = std::enable_if_t<std::is_same<Head,T>::value>>
			constexpr array(Head head, Tail... tail) :
				data_{head, tail...}
			{}

			template<std::size_t... Is>
			constexpr array(const T* const arr, std::index_sequence<Is...>) :
					data_{ arr[Is]... }
			{}

			constexpr const T* const data() const
			{
				return &data_[0];
			}

			constexpr const T operator[](std::size_t i) const
			{
				return data_[i];
			}

			constexpr std::size_t size() const
			{
				return Size;
			}

			template<std::size_t Begin, std::size_t End>
			constexpr array<T, End - Begin> subarray() const
			{
				return make_array<Begin, End>(data_);
			}
			/*
			template<typename Lhs, typename Rhs, std::size_t LhsN, std::size_t RhsN>
			friend constexpr bool operator==(const array<Lhs,LhsN>& lhs, const array<Rhs,RhsN>& rhs)
			{
				if(LhsN == RhsN)
				{
					for (std::size_t i = 0; i < LhsN; ++i)
					{
						if (lhs[i] != rhs[i])
							return false;
					}

					return true;
				}
				else
					return false;
			}

			template<typename Lhs, typename Rhs, std::size_t LhsN, std::size_t RhsN>
			friend constexpr bool operator!=(const array<Lhs,LhsN>& lhs, const array<Rhs,RhsN>& rhs)
			{
				return !(lhs == rhs);
			}
		    */

		private:
			const T data_[Size];
		};

		template<std::size_t Begin, std::size_t End, typename T>
		constexpr array<T, End - Begin> make_array(const T* const arr)
		{
			return array<T, End - Begin>{ arr + Begin, std::make_index_sequence<End - Begin>{} };
		}

		template<typename T, std::size_t N>
		constexpr array<T, N> make_array(const T(&arr)[N])
		{
			return make_array<0, N>(arr);
		}
	}
}
#endif