/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <iostream>
#include <stdexcept>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class component_a
{
public:
	component_a()
	{
		std::cout << "component_a::ctor() 시작" << std::endl;



		std::cout << "component_a::ctor()   끝" << std::endl;
	}

	~component_a()
	{
		std::cout << "component_a::dtor() 시작" << std::endl;



		std::cout << "component_a::dtor()   끝" << std::endl;
	}

	void test()
	{
		std::cout << "component_a::test() 시작" << std::endl;



		std::cout << "component_a::test()   끝" << std::endl;
	}
};








/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class component_b
{
public:
	std::uint8_t* _buffer_0 { nullptr };
	std::uint8_t* _buffer_1 { nullptr };


public:
	component_b()
	{
		std::cout << "component_b::ctor() 시작" << std::endl;


		_buffer_0 = new (std::nothrow)std::uint8_t[1024];
		try
		{
			func();

			_buffer_1 = new (std::nothrow)std::uint8_t[1024];
		}
		catch (...)
		{
			// 이 객체는 온전히 생성이 안되었으므로, 소멸자가 호출되지 않음.


			//-------------------------------------------------------------------
			// RAII관점에서 여기서 이 객체에 대한 리소스를 정리 해야 함!!!
			{
				if (_buffer_0)
				{
					std::cout << "component_b::ctor() delete _buffer_0" << std::endl;
					delete _buffer_0;
				}


				if (_buffer_1)
				{
					std::cout << "component_b::ctor() delete _buffer_1" << std::endl;
					delete _buffer_1;
				}
			}
			//-------------------------------------------------------------------


			std::cout << "component_b::ctor() 다시 예외 발생 시키기" << std::endl;
			throw std::runtime_error("Exception in component_b::ctor()");
		}



		std::cout << "component_b::ctor()   끝" << std::endl;
	}

	~component_b()
	{
		// 호출 안됨


		std::cout << "component_b::dtor() 시작" << std::endl;


		delete _buffer_0;
		delete _buffer_1;


		std::cout << "component_b::dtor()   끝" << std::endl;



		// component_a::dtor()은 호출 됨
	}

	void func()
	{
		std::cout << "component_b::func() 시작" << std::endl;



		std::cout << "component_b::func() 예외 발생 시키기" << std::endl;
		throw std::runtime_error("Exception in component_b::func()");



		std::cout << "component_b::func()   끝" << std::endl;
	}
};








/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class component_c
{
public:
	component_c()
	{
		std::cout << "component_c::ctor() 시작" << std::endl;



		std::cout << "component_c::ctor()   끝" << std::endl;
	}

	~component_c()
	{
		std::cout << "component_c::dtor() 시작" << std::endl;



		std::cout << "component_c::dtor()   끝" << std::endl;
	}

	void test()
	{
		std::cout << "component_c::test() 시작" << std::endl;



		std::cout << "component_c::test()   끝" << std::endl;
	}
};








/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class module_engine
{
public:
	component_a _a;
	component_b _b;
	component_c _c;

public:
	module_engine()
	{
		std::cout << "module_engine::ctor() 시작" << std::endl;



		std::cout << "module_engine::ctor()   끝" << std::endl;
	}

	~module_engine()
	{
		std::cout << "module_engine::dtor() 시작" << std::endl;



		std::cout << "module_engine::dtor()   끝" << std::endl;
	}

	void func()
	{
		std::cout << "module_engine::func() 시작" << std::endl;



		std::cout << "module_engine::func()   끝" << std::endl;
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test()
{
	std::cout << "::test() 시작" << std::endl;



	try
	{
		module_engine e;

		e.func();
	}
	catch (...)
	{
		std::cout << "::test() 예외 발생" << std::endl;
	}



	std::cout << "::test()   끝" << std::endl;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int main()
{
	std::cout << "시작" << std::endl;
	test();
	std::cout << "끝" << std::endl;

	return 0;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// 결과

/*

시작
::test() 시작
component_a::ctor() 시작
component_a::ctor()   끝
component_b::ctor() 시작
component_b::func() 시작
component_b::func() 예외 발생 시키기
component_b::ctor() delete _buffer_0
component_b::ctor() 다시 예외 발생 시키기
component_a::dtor() 시작
component_a::dtor()   끝
::test() 예외 발생
::test()   끝
끝

*/

/*
* component_c의 생성자와 소멸자는 호출되지 않음.
*/
