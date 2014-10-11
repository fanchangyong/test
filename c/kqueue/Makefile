all:kqueue_echo_client kqueue_echo_server conn

conn:conn.c
	cc $< -o $@

kqueue_echo_client:kqueue_echo_client.c
	cc $< -o $@

kqueue_echo_server:kqueue_echo_server.c
	cc $< -o $@
