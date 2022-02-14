// torture your compiler

template <int i>
void bar();

template <int i>
void foo()
{
	bar<i>();
	char baz[i];
}

template <int i>
void bar()
{
	foo<i - 1>();
}

int main(void)
{
	foo<2000>();
	return 0;
}