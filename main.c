#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> 

int main(int argc, char* argv[]) {
	int (*func1ptr)();
	const char* (*func2ptr)();

	void* handle = NULL;

	const char* errmsg = NULL;
	
	// ./libfunc.so makes it so you don't need to do anything 
	// more telling where libfunc is (not included in og example)
	handle = dlopen("./libfunc.so", RTLD_LAZY);

	if (!handle) {
		fprintf(stderr, "dlopen() %s\n", dlerror());
		exit(1);
	}
	dlerror();

	func1ptr = (int (*)()) dlsym(handle, "func1");

	errmsg = dlerror();
	if (errmsg) {
		fprintf(stderr, "dlsym() for func1 %s\n", errmsg);
		dlclose(handle);
		exit(1);
	}

	func2ptr = (const char* (*)) dlsym(handle, "func2");

	errmsg = dlerror();
	if (errmsg) {
		fprintf(stderr, "dlsym() for func1 %s\n", errmsg);
		dlclose(handle);
		exit(1);
	}
	
	int func1returns = (*func1ptr)();
	const char* func2returns = (*func2ptr)();
	printf("func1 returns: %d\n", func1returns);
	printf("func2 returns: %s\n", func2returns);

	dlclose(handle);
	return 0;
}

