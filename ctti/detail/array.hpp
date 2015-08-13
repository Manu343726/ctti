#pragma once

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
			template<typename Head, typename... Tail, typename = std::enable_if_t<std::is_same<Head,T>::value>>
			explicit constexpr array(Head head, Tail... tail) :
				data_{head, tail...}
			{}

			template<std::size_t... Is>
			constexpr array(const T* const arr, std::index_sequence<Is...>) :
					data_{ arr[Is]... }
			{}

			constexpr const T* data() const
			{
				return &data_[0];
			}

			constexpr T operator[](std::size_t i) const
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

		namespace
		{
			template<typename T, std::size_t... Is>
			constexpr auto make_array(const T* arr, std::index_sequence<Is...>)
			{
				return array<T, sizeof...(Is)>{ arr[Is]... };
			}
		}

		template<std::size_t Begin, std::size_t End, typename T>
		constexpr array<T, End - Begin> make_array(const T* arr)
		{
			return make_array( arr + Begin, std::make_index_sequence<End - Begin>{} );
		}

		template<typename T, std::size_t N>
		constexpr array<T, N> make_array(const T(&arr)[N])
		{
			return make_array(arr, std::make_index_sequence<N>{});
		}
	}
}