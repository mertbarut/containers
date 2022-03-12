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

template <>		// <- comment this template out and run "make inf" to let chaos reign
void foo<1>()
{

}

int main(void)
{
	foo<200>();
	return 0;
}