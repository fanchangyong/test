use test;
drop table if exists student;
drop table if exists score;

create table student(id int auto_increment primary key,name varchar(64),addr varchar(64));
create table score(id int auto_increment primary key,stu_id int,score int);

insert into student(name,addr) values("kevin","beijing huilongguan");
insert into student(name,addr) values("david","shanghai huangfu");
insert into student(name,addr) values("jack","NYC");
insert into student(name,addr) values("michael","Los Angelos");
insert into student(name,addr) values("michael","Chicago");
insert into student(name,addr) values("michael","San Francisco"); -- another michael,bug from San Francisco

insert into score(stu_id,score) values(1,100);
insert into score(stu_id,score) values(2,80);
insert into score(stu_id,score) values(3,85);
insert into score(stu_id,score) values(4,95);


