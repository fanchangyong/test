#! /bin/sh
go build golang
go install golang
go build golang_main
go install golang_main
go build golang_test
go install golang_test
