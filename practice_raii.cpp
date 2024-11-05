/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <iostream>
#include <memory>
#include <stdexcept>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class a_component
{
public:
	a_component()
	{
		std::cout << "a_component::ctor() 시작" << std::endl;



		std::cout << "a_component::ctor()   끝" << std::endl;
	}

	~a_component()
	{
		std::cout << "a_component::dtor() 시작" << std::endl;



		std::cout << "a_component::dtor()   끝" << std::endl;
	}

	void test()
	{
		std::cout << "a_component::test() 시작" << std::endl;



		std::cout << "a_component::test()   끝" << std::endl;
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class b_component
{
public:
	std::uint32_t*                 _buffer_0 { nullptr };
	std::unique_ptr<std::uint32_t> _buffer_1;
	std::uint32_t*                 _buffer_2 { nullptr };

public:
	b_component()
	{
		std::cout << "b_component::ctor() 시작" << std::endl;

		// RAII(Resource Acquisition Is Initialization) 형태로 클래스 작성시
		// 직접적으로 new를 사용하명 아래와 같은 불편이 있음으로
		// std::unique_ptr, std::shared_ptr를 사용하는 것이 좋음.
		// 가급적 new 사용을 안하는 것이 좋다.

		std::cout << "b_component::ctor() new _buffer_0" << std::endl;
		_buffer_0 = new (std::nothrow)std::uint32_t[1024];
		std::cout << "b_component::ctor() _buffer_0 = " << _buffer_0 << std::endl;

		std::cout << "b_component::ctor() new _buffer_1" << std::endl;
		_buffer_1 = std::make_unique<std::uint32_t>(1024);
		std::cout << "b_component::ctor() _buffer_1 = " << _buffer_1.get() << std::endl;

		try
		{
			func();

			std::cout << "b_component::ctor() new _buffer_2" << std::endl;
			_buffer_2 = new (std::nothrow)std::uint32_t[1024];
			std::cout << "b_component::ctor() _buffer_2 = " << _buffer_2 << std::endl;
		}
		catch (...)
		{
			//-------------------------------------------------------------------
			// RAII관점에서 여기서 이 객체에 대한 리소스를 정리 해야 함!!!
			{
				if (_buffer_0)
				{
					std::cout << "b_component::ctor() delete _buffer_0" << std::endl;
					delete _buffer_0;
				}

				// _buffer_1.reset(); // std::unique_ptr는 자동으로 해제됨.

				if (_buffer_2)
				{
					std::cout << "b_component::ctor() delete _buffer_2" << std::endl;
					delete _buffer_2;
				}
			}
			//-------------------------------------------------------------------


			std::cout << "b_component::ctor() 다시 예외 발생 시키기" << std::endl;
			throw std::runtime_error("Exception in b_component::ctor()");
		}



		// 이 객체는 온전히 생성이 안되었으므로, 소멸자가 호출되지 않음.

		std::cout << "b_component::ctor()   끝" << std::endl;
	}

	~b_component()
	{
		// b_component::dtor()은 호출 안됨
		// a_component::dtor()은 호출 됨


		std::cout << "b_component::dtor() 시작" << std::endl;


		delete _buffer_0;
		delete _buffer_2;


		std::cout << "b_component::dtor()   끝" << std::endl;
	}

	void func()
	{
		std::cout << "b_component::func() 시작" << std::endl;



		std::cout << "b_component::func() 예외 발생 시키기" << std::endl;
		throw std::runtime_error("Exception in b_component::func()");



		std::cout << "b_component::func()   끝" << std::endl;
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class c_component
{
public:
	c_component()
	{
		std::cout << "c_component::ctor() 시작" << std::endl;



		std::cout << "c_component::ctor()   끝" << std::endl;
	}

	~c_component()
	{
		std::cout << "c_component::dtor() 시작" << std::endl;



		std::cout << "c_component::dtor()   끝" << std::endl;
	}

	void test()
	{
		std::cout << "c_component::test() 시작" << std::endl;



		std::cout << "c_component::test()   끝" << std::endl;
	}
};








/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class engine_module
{
public:
	a_component _a;
	b_component _b;
	c_component _c;

public:
	engine_module()
	{
		std::cout << "engine_module::ctor() 시작" << std::endl;



		std::cout << "engine_module::ctor()   끝" << std::endl;
	}

	~engine_module()
	{
		std::cout << "engine_module::dtor() 시작" << std::endl;



		std::cout << "engine_module::dtor()   끝" << std::endl;
	}

	void func()
	{
		std::cout << "engine_module::func() 시작" << std::endl;



		std::cout << "engine_module::func()   끝" << std::endl;
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test()
{
	std::cout << "::test() 시작" << std::endl;



	try
	{
		engine_module e;

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
a_component::ctor() 시작
a_component::ctor()   끝
b_component::ctor() 시작
b_component::ctor() new _buffer_0
b_component::ctor() _buffer_0 = 0000021E9FCC7790
b_component::ctor() new _buffer_1
b_component::ctor() _buffer_1 = 0000021E9FCB7490
b_component::func() 시작
b_component::func() 예외 발생 시키기
b_component::ctor() delete _buffer_0
b_component::ctor() 다시 예외 발생 시키기
a_component::dtor() 시작
a_component::dtor()   끝
::test() 예외 발생
::test()   끝
끝

*/

/*
* c_component의 생성자와 소멸자는 호출되지 않음.
*/

#if 0

typedef struct  _test_packed_struct_t
{
	unsigned short int e0;
	unsigned short int e1;
	unsigned long  int e2 ;
}
__attribute__((__packed__)) test_packed_struct_t;


typedef struct  _test_struct_t
{
	unsigned short int    e0;
//	unsigned short int    reserved; // 추가시 2바이트 패딩되어서 sDram에서도 DABORT 발생 안함
	test_packed_struct_t  e1;
}
test_struct_t;

void test_packed_struct_function(test_packed_struct_t* p)
{
	if (p->e2 == 0xffffffff) // <!-- DABORT 발생
	{
		console_printfln("p->e1.e2==0xffffffff");
	}
	else
	{
		console_printfln("p->e1.e2!=0xffffffff");
	}
}

void test_function(void)
{
	test_struct_t i;
	test_struct_t* p;


	p = &i;                            // DABORT 발생 안함 (sram)
	p = (test_struct_t*)(0x80D00000U); // DABORT 발생 함   (sDram)
	memset(&i, 0xff, sizeof(i));
	memset(p, 0xff, sizeof(i));


	console_printfln("sizeof(test_struct_t) = %u", sizeof(i));


	test_packed_struct_function(&p->e1);
}

#endif
