#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

uv_loop_t* loop;

void close_cb(uv_handle_t* handle)
{
	printf("close cb\n");
}

void alloc_cb(uv_handle_t* handle,size_t suggested_size,uv_buf_t* buf)
{
	buf->base = malloc(suggested_size);
	buf->len = suggested_size;
	return;
}

void read_cb(uv_stream_t* handle,ssize_t nread,const uv_buf_t *buf)
{
	if(nread<0)
	{
		if(nread==UV_EOF)
		{
			printf("EOF\n");
		}
		else
		{
			printf("read error:%d\n",nread);
		}
		uv_close(handle,close_cb);
	}
	else if(nread==0)
	{
		printf("EOF\n");
		uv_close(handle,close_cb);
	}
	else
	{
		printf("Read:%s\n",buf->base);
	}
	return;
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status == -1) {
				printf("status error\n");
        // error!
        return;
    }
		printf("New Connection\n");
		uv_tcp_t *pclient = malloc(sizeof(uv_tcp_t));
		uv_tcp_init(loop,pclient);
		if(uv_accept(server,pclient)==0)
		{
			uv_read_start((uv_stream_t*)pclient,alloc_cb,read_cb);
		}
}

int main() {
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in bind_addr;
 		uv_ip4_addr("0.0.0.0", 7000,&bind_addr);
    uv_tcp_bind(&server, (struct sockaddr*)&bind_addr,0);
    int r = uv_listen((uv_stream_t*) &server, 128, on_new_connection);
    if (r) {
				printf("listen error\n");
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}

