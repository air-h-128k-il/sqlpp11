/*
 * Copyright (c) 2013, Roland Bock
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "TabSample.h"
#include "MockDb.h"
#include "is_regular.h"
#include <sqlpp11/functions.h>

#include <iostream>

DbMock db = {};

int main()
{
	TabSample t;
	TabFoo f; 

	// empty parameter lists
	{
		using T = typename sqlpp::detail::get_parameter_tuple<decltype(t.alpha)>::type;
		static_assert(std::is_same<T, std::tuple<>>::value, "type requirement");
	}

	// single parameter
	{
		using T = typename sqlpp::detail::get_parameter_tuple<decltype(parameter(t.alpha))>::type;
		static_assert(std::is_same<T, std::tuple<decltype(parameter(t.alpha))>>::value, "type requirement");
	}

	// single parameter
	{
		using T = typename sqlpp::detail::get_parameter_tuple<decltype(parameter(t.alpha))>::type;
		static_assert(std::is_same<T, std::tuple<decltype(parameter(t.alpha))>>::value, "type requirement");
	}

	// single parameter in expression
	{
		using T = typename sqlpp::detail::get_parameter_tuple<decltype(t.alpha == parameter(t.alpha))>::type;
		static_assert(std::is_same<T, std::tuple<decltype(parameter(t.alpha))>>::value, "type requirement");
	}

	// single parameter in larger expression
	{
		using T = typename sqlpp::detail::get_parameter_tuple<decltype(t.beta.like("%") and t.alpha == parameter(t.alpha) or t.gamma != false)>::type;
		static_assert(std::is_same<T, std::tuple<decltype(parameter(t.alpha))>>::value, "type requirement");
	}

	// three parameters in expression
	{
		using T = typename sqlpp::detail::get_parameter_tuple<decltype(t.beta.like(parameter(t.beta)) and t.alpha == parameter(t.alpha) or t.gamma != parameter(t.gamma))>::type;
		static_assert(std::tuple_size<T>::value == 3, "type requirement");
		static_assert(std::is_same<T, std::tuple<decltype(parameter(t.beta)), decltype(parameter(t.alpha)),decltype(parameter(t.gamma))>>::value, "type requirement");
	}


	return 0;
}
