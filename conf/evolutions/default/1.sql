# --- Created by Ebean DDL
# To stop Ebean DDL generation, remove this comment and start using Evolutions

# --- !Ups

create table task (
  id                        bigint not null,
  label                     varchar(255),
  constraint pk_task primary key (id))
;

create table type (
  id                        bigint not null,
  name                      varchar(255),
  constraint pk_type primary key (id))
;

create sequence task_seq;

create sequence type_seq;




# --- !Downs

SET REFERENTIAL_INTEGRITY FALSE;

drop table if exists task;

drop table if exists type;

SET REFERENTIAL_INTEGRITY TRUE;

drop sequence if exists task_seq;

drop sequence if exists type_seq;

