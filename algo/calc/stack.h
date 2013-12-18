typedef struct cstack cstack;
struct cstack
{
	int pos;
	int maxn;
	void** pv;
};

cstack* create_stack(int n);
void push(cstack* stack,void* v);
void* pop(cstack* stack);
