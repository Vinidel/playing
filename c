[33mcommit c4f5becfe638441854dcc058788281b3c841fd4a[m
Author: Vinícius Deláscio <vinidroid@gmail.com>
Date:   Sun Oct 18 15:11:38 2015 +1100

    init

[1mdiff --git a/.gitignore b/.gitignore[m
[1mnew file mode 100644[m
[1mindex 0000000..8570daf[m
[1m--- /dev/null[m
[1m+++ b/.gitignore[m
[36m@@ -0,0 +1,15 @@[m
[32m+[m[32mlogs[m
[32m+[m[32mproject/project[m
[32m+[m[32mproject/target[m
[32m+[m[32mtarget[m
[32m+[m[32mtmp[m
[32m+[m[32m.history[m
[32m+[m[32mdist[m
[32m+[m[32m/.idea[m
[32m+[m[32m/*.iml[m
[32m+[m[32m/out[m
[32m+[m[32m/.idea_modules[m
[32m+[m[32m/.classpath[m
[32m+[m[32m/.project[m
[32m+[m[32m/RUNNING_PID[m
[32m+[m[32m/.settings[m
[1mdiff --git a/Procfile b/Procfile[m
[1mnew file mode 100644[m
[1mindex 0000000..220c3e6[m
[1m--- /dev/null[m
[1m+++ b/Procfile[m
[36m@@ -0,0 +1 @@[m
[32m+[m[32mweb: target/universal/stage/bin/to-do-list -Dhttp.port=${PORT} -DapplyEvolutions.default=true -Ddb.default.url=${DATABASE_URL} -Ddb.default.driver=org.postgresql.Driver[m
[1mdiff --git a/README b/README[m
[1mnew file mode 100644[m
[1mindex 0000000..da7c378[m
[1m--- /dev/null[m
[1m+++ b/README[m
[36m@@ -0,0 +1,4 @@[m
[32m+[m[32mThis is your new Play application[m
[32m+[m[32m=====================================[m
[32m+[m
[32m+[m[32mThis file will be packaged with your application, when using `play dist`.[m
[1mdiff --git a/app/controllers/Application.java b/app/controllers/Application.java[m
[1mnew file mode 100644[m
[1mindex 0000000..a351968[m
[1m--- /dev/null[m
[1m+++ b/app/controllers/Application.java[m
[36m@@ -0,0 +1,47 @@[m
[32m+[m[32mpackage controllers;[m
[32m+[m
[32m+[m[32mimport play.*;[m
[32m+[m[32mimport play.mvc.*;[m
[32m+[m[32mimport play.data.*;[m
[32m+[m[32mimport play.data.Form;[m
[32m+[m[32mimport models.*;[m
[32m+[m[32mimport views.html.*;[m
[32m+[m
[32m+[m[32mpublic class Application extends Controller {[m
[32m+[m
[32m+[m[32m    static Form<Task> taskForm = Form.form(Task.class);[m
[32m+[m
[32m+[m[32m    public static Result index() {[m
[32m+[m[32m        //return ok("Your new application is ready.");[m
[32m+[m
[32m+[m[32m        return redirect(routes.Application.tasks());[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    public static Result tasks(){[m
[32m+[m[32m      return ok([m
[32m+[m[32m        views.html.index.render(Task.all(), taskForm)[m
[32m+[m[32m      );[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    public static Result newTask(){[m
[32m+[m[32m      Form<Task> filledForm = taskForm.bindFromRequest();[m
[32m+[m[32m      if (filledForm.hasErrors()) {[m
[32m+[m[32m        return badRequest([m
[32m+[m[32m          views.html.index.render(Task.all(), filledForm)[m
[32m+[m[32m        );[m
[32m+[m[32m      } else {[m
[32m+[m[32m        Task.create(filledForm.get());[m
[32m+[m[32m        return redirect(routes.Application.tasks());[m
[32m+[m[32m      }[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    public static Result deleteTask(Long id){[m
[32m+[m[32m      Task.delete(id);[m
[32m+[m[32m      return redirect(routes.Application.tasks());[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    public static Result types(){[m
[32m+[m[32m      return ok(views.html.types.render());[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m}[m
[1mdiff --git a/app/models/MyServerConfigStartup.java b/app/models/MyServerConfigStartup.java[m
[1mnew file mode 100644[m
[1mindex 0000000..7700f08[m
[1m--- /dev/null[m
[1m+++ b/app/models/MyServerConfigStartup.java[m
[36m@@ -0,0 +1,12 @@[m
[32m+[m[32mpackage models;[m
[32m+[m
[32m+[m[32mimport com.avaje.ebean.config.ServerConfig;[m
[32m+[m[32mimport com.avaje.ebean.event.ServerConfigStartup;[m
[32m+[m
[32m+[m[32mpublic class MyServerConfigStartup implements ServerConfigStartup {[m
[32m+[m
[32m+[m[32m    @Override[m
[32m+[m[32m    public void onStart(ServerConfig serverConfig){[m
[32m+[m[32m        serverConfig.setDatabaseSequenceBatchSize(1);[m
[32m+[m[32m    }[m
[32m+[m[32m}[m
[1mdiff --git a/app/models/Task.java b/app/models/Task.java[m
[1mnew file mode 100644[m
[1mindex 0000000..71bc629[m
[1m--- /dev/null[m
[1m+++ b/app/models/Task.java[m
[36m@@ -0,0 +1,34 @@[m
[32m+[m[32mpackage models;[m
[32m+[m
[32m+[m[32mimport java.util.*;[m
[32m+[m[32mimport play.data.validation.Constraints.*;[m
[32m+[m[32mimport play.db.ebean.*;[m
[32m+[m
[32m+[m[32mimport javax.persistence.*;[m
[32m+[m
[32m+[m[32m@Entity[m
[32m+[m[32mpublic class Task extends Model {[m
[32m+[m[32m  @Id[m
[32m+[m[32m  public Long id;[m
[32m+[m
[32m+[m[32m  @Required[m
[32m+[m[32m  public String label;[m
[32m+[m
[32m+[m[32m  //DataSource ds = DB.getDatasource();[m
[32m+[m
[32m+[m[32m  public static Finder<Long,Task> find = new Finder([m
[32m+[m[32m    Long.class, Task.class[m
[32m+[m[32m  );[m
[32m+[m
[32m+[m[32m  public static List<Task> all(){[m
[32m+[m[32m    return find.all();[m
[32m+[m[32m  }[m
[32m+[m
[32m+[m[32m  public static void create(Task task){[m
[32m+[m[32m      task.save();[m
[32m+[m[32m  }[m
[32m+[m
[32m+[m[32m  public static void delete(Long id){[m
[32m+[m[32m    find.ref(id).delete();[m
[32m+[m[32m  }[m
[32m+[m[32m}[m
[1mdiff --git a/app/models/Type.java b/app/models/Type.java[m
[1mnew file mode 100644[m
[1mindex 0000000..105e9a0[m
[1m--- /dev/null[m
[1m+++ b/app/models/Type.java[m
[36m@@ -0,0 +1,19 @@[m
[32m+[m[32mpackage models;[m
[32m+[m
[32m+[m[32mimport java.util.*;[m
[32m+[m[32mimport play.data.validation.Constraints.*;[m
[32m+[m[32mimport play.db.ebean.*;[m
[32m+[m
[32m+[m[32mimport javax.persistence.*;[m
[32m+[m
[32m+[m[32m  public class Type extends Model{[m
[32m+[m
[32m+[m[32m      public Long id;[m
[32m+[m[32m      public String Name;[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m[41m      [m
[32m+[m
[32m+[m
[32m+[m[32m  }[m
[1mdiff --git a/app/views/index.scala.html b/app/views/index.scala.html[m
[1mnew file mode 100644[m
[1mindex 0000000..7e22fba[m
[1m--- /dev/null[m
[1m+++ b/app/views/index.scala.html[m
[36m@@ -0,0 +1,27 @@[m
[32m+[m[32m@(tasks: List[Task], taskForm: Form[Task])[m
[32m+[m
[32m+[m[32m@import helper._[m
[32m+[m
[32m+[m[32m@main("Todo list") {[m
[32m+[m
[32m+[m[32m    <h1>@tasks.size() task(s)</h1>[m
[32m+[m
[32m+[m[32m    <ul>[m
[32m+[m[32m      @for(task <- tasks){[m
[32m+[m[32m        <li>[m
[32m+[m[32m            @task.label[m
[32m+[m[32m            @form(routes.Application.deleteTask(task.id)){[m
[32m+[m[32m              <input type="submit" value="Delete">[m
[32m+[m[32m            }[m
[32m+[m[32m        </li>[m
[32m+[m[32m      }[m
[32m+[m[32m    </ul>[m
[32m+[m
[32m+[m[32m    <h2>Add a new task</h2>[m
[32m+[m[32m    @form(routes.Application.newTask()){[m
[32m+[m
[32m+[m[32m      @inputText(taskForm("label"))[m
[32m+[m
[32m+[m[32m      <input type="submit" name="Create" value="Create">[m
[32m+[m[32m    }[m
[32m+[m[32m}[m
[1mdiff --git a/app/views/main.scala.html b/app/views/main.scala.html[m
[1mnew file mode 100644[m
[1mindex 0000000..6c72d80[m
[1m--- /dev/null[m
[1m+++ b/app/views/main.scala.html[m
[36m@@ -0,0 +1,15 @@[m
[32m+[m[32m@(title: String)(content: Html)[m
[32m+[m
[32m+[m[32m<!DOCTYPE html>[m
[32m+[m
[32m+[m[32m<html>[m
[32m+[m[32m    <head>[m
[32m+[m[32m        <title>@title</title>[m
[32m+[m[32m        <link rel="stylesheet" media="screen" href="@routes.Assets.at("stylesheets/main.css")">[m
[32m+[m[32m        <link rel="shortcut icon" type="image/png" href="@routes.Assets.at("images/favicon.png")">[m
[32m+[m[32m        <script src="@routes.Assets.at("javascripts/jquery-1.9.0.min.js")" type="text/javascript"></script>[m
[32m+[m[32m    </head>[m
[32m+[m[32m    <body>[m
[32m+[m[32m        @content[m
[32m+[m[32m    </body>[m
[32m+[m[32m</html>[m
[1mdiff --git a/app/views/types.scala.html b/app/views/types.scala.html[m
[1mnew file mode 100644[m
[1mindex 0000000..baddcea[m
[1m--- /dev/null[m
[1m+++ b/app/views/types.scala.html[m
[36m@@ -0,0 +1,16 @@[m
[32m+[m[32m@()[m
[32m+[m
[32m+[m[32m@import helper._[m
[32m+[m
[32m+[m[32m@main("Todo list types") {[m
[32m+[m
[32m+[m[32m    <h1> type(s)</h1>[m
[32m+[m
[32m+[m[32m    <ul>[m
[32m+[m
[32m+[m[32m    </ul>[m
[32m+[m
[32m+[m[32m    <h2>Add a new Type</h2>[m
[32m+[m
[32m+[m[32m      <input type="submit" name="Create" value="Create">[m
[32m+[m[32m    }[m
[1mdiff --git a/build.sbt b/build.sbt[m
[1mnew file mode 100644[m
[1mindex 0000000..40e1798[m
[1m--- /dev/null[m
[1m+++ b/build.sbt[m
[36m@@ -0,0 +1,12 @@[m
[32m+[m[32mname := "to-do-list"[m
[32m+[m
[32m+[m[32mversion := "1.0-SNAPSHOT"[m
[32m+[m
[32m+[m[32mlibraryDependencies ++= Seq([m
[32m+[m[32m  javaJdbc,[m
[32m+[m[32m  javaEbean,[m
[32m+[m[32m  cache,[m
[32m+[m[32m  "postgresql" % "postgresql" % "8.4-702.jdbc4"[m
[32m+[m[32m)[m
[32m+[m
[32m+[m[32mplay.Project.playJavaSettings[m
[1mdiff --git a/conf/application.conf b/conf/application.conf[m
[1mnew file mode 100644[m
[1mindex 0000000..47177ae[m
[1m--- /dev/null[m
[1m+++ b/conf/application.conf[m
[36m@@ -0,0 +1,68 @@[m
[32m+[m[32m# This is the main configuration file for the application.[m
[32m+[m[32m# ~~~~~[m
[32m+[m
[32m+[m[32m# Secret key[m
[32m+[m[32m# ~~~~~[m
[32m+[m[32m# The secret key is used to secure cryptographics functions.[m
[32m+[m[32m# If you deploy your application to several instances be sure to use the same key![m
[32m+[m[32mapplication.secret="sx8rf>9@TO43`yRoT`RD5E^fekjUjlI[P:KZo:ASV<8YDTXl?Cv0UDv?nIvjWE_l"[m
[32m+[m
[32m+[m[32m# The application languages[m
[32m+[m[32m# ~~~~~[m
[32m+[m[32mapplication.langs="en"[m
[32m+[m
[32m+[m[32m# Global object class[m
[32m+[m[32m# ~~~~~[m
[32m+[m[32m# Define the Global object class for this application.[m
[32m+[m[32m# Default to Global in the root package.[m
[32m+[m[32m# application.global=Global[m
[32m+[m
[32m+[m[32m# Router[m
[32m+[m[32m# ~~~~~[m
[32m+[m[32m# Define the Router object to use for this application.[m
[32m+[m[32m# This router will be looked up first when the application is starting up,[m
[32m+[m[32m# so make sure this is the entry point.[m
[32m+[m[32m# Furthermore, it's assumed your route file is named properly.[m
[32m+[m[32m# So for an application router like `conf/my.application.Router`,[m
[32m+[m[32m# you may need to define a router file `my.application.routes`.[m
[32m+[m[32m# Default to Routes in the root package (and `conf/routes`)[m
[32m+[m[32m# application.router=my.application.Routes[m
[32m+[m
[32m+[m[32m# Database configuration[m
[32m+[m[32m# ~~~~~[m
[32m+[m[32m# You can declare as many datasources as you want.[m
[32m+[m[32m# By convention, the default datasource is named `default`[m
[32m+[m[32m#[m
[32m+[m[32mdb.default.driver=org.h2.Driver[m
[32m+[m[32mdb.default.url="jdbc:h2:mem:play"[m
[32m+[m[32m# db.default.user=sa[m
[32m+[m[32m# db.default.password=""[m
[32m+[m[32m#[m
[32m+[m[32m# You can expose this datasource via JNDI if needed (Useful for JPA)[m
[32m+[m[32m# db.default.jndiName=DefaultDS[m
[32m+[m
[32m+[m[32m# Evolutions[m
[32m+[m[32m# ~~~~~[m
[32m+[m[32m# You can disable evolutions if needed[m
[32m+[m[32m# evolutionplugin=disabled[m
[32m+[m
[32m+[m[32m# Ebean configuration[m
[32m+[m[32m# ~~~~~[m
[32m+[m[32m# You can declare as many Ebean servers as you want.[m
[32m+[m[32m# By convention, the default server is named `default`[m
[32m+[m[32m#[m
[32m+[m[32mebean.default="models.*"[m
[32m+[m
[32m+[m[32m# Logger[m
[32m+[m[32m# ~~~~~[m
[32m+[m[32m# You can also configure logback (http://logback.qos.ch/),[m
[32m+[m[32m# by providing an application-logger.xml file in the conf directory.[m
[32m+[m
[32m+[m[32m# Root logger:[m
[32m+[m[32mlogger.root=ERROR[m
[32m+[m
[32m+[m[32m# Logger used by the framework:[m
[32m+[m[32mlogger.play=INFO[m
[32m+[m
[32m+[m[32m# Logger provided to your application:[m
[32m+[m[32mlogger.application=DEBUG[m
[1mdiff --git a/conf/evolutions/default/1.sql b/conf/evolutions/default/1.sql[m
[1mnew file mode 100644[m
[1mindex 0000000..3c3c1c7[m
[1m--- /dev/null[m
[1m+++ b/conf/evolutions/default/1.sql[m
[36m@@ -0,0 +1,26 @@[m
[32m+[m[32m# --- Created by Ebean DDL[m
[32m+[m[32m# To stop Ebean DDL generation, remove this comment and start using Evolutions[m
[32m+[m
[32m+[m[32m# --- !Ups[m
[32m+[m
[32m+[m[32mcreate table task ([m
[32m+[m[32m  id                        bigint not null,[m
[32m+[m[32m  label                     varchar(255),[m
[32m+[m[32m  constraint pk_task primary key (id))[m
[32m+[m[32m;[m
[32m+[m
[32m+[m[32mcreate sequence task_seq;[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m[32m# --- !Downs[m
[32m+[m
[32m+[m[32mSET REFERENTIAL_INTEGRITY FALSE;[m
[32m+[m
[32m+[m[32mdrop table if exists task;[m
[32m+[m
[32m+[m[32mSET REFERENTIAL_INTEGRITY TRUE;[m
[32m+[m
[32m+[m[32mdrop sequence if exists task_seq;[m
[32m+[m
[1mdiff --git a/conf/routes b/conf/routes[m
[1mnew file mode 100644[m
[1mindex 0000000..ba68d24[m
[1m--- /dev/null[m
[1m+++ b/conf/routes[m
[36m@@ -0,0 +1,17 @@[m
[32m+[m[32m# Routes[m
[32m+[m[32m# This file defines all application routes (Higher priority routes first)[m
[32m+[m[32m# ~~~~[m
[32m+[m
[32m+[m[32m# Home page[m
[32m+[m[32mGET     /                           controllers.Application.index()[m
[32m+[m
[32m+[m[32m#Tasks[m
[32m+[m[32mGET     /tasks                      controllers.Application.tasks()[m
[32m+[m[32mPOST    /tasks                      controllers.Application.newTask()[m
[32m+[m[32mPOST    /tasks/:id/delete           controllers.Application.deleteTask(id: Long)[m
[32m+[m
[32m+[m[32m#Types[m
[32m+[m[32mGET    /types                       controllers.Application.types()[m
[32m+[m
[32m+[m[32m# Map static resources from the /public folder to the /assets URL path[m
[32m+[m[32mGET     /assets/*file               controllers.Assets.at(path="/public", file)[m
[1mdiff --git a/notes.js b/notes.js[m
[1mnew file mode 100644[m
[1mindex 0000000..1179279[m
[1m--- /dev/null[m
[1m+++ b/notes.js[m
[36m@@ -0,0 +1,2 @@[m
[32m+[m[32m - Play templates are compiled to standard Java methods, here as views.html.index.render(String message).[m
[32m+[m[32m - The Form object encapsulates a HTML, what does that mean?[m
[1mdiff --git a/project/build.properties b/project/build.properties[m
[1mnew file mode 100644[m
[1mindex 0000000..0974fce[m
[1m--- /dev/null[m
[1m+++ b/project/build.properties[m
[36m@@ -0,0 +1 @@[m
[32m+[m[32msbt.version=0.13.0[m
[1mdiff --git a/project/plugins.sbt b/project/plugins.sbt[m
[1mnew file mode 100644[m
[1mindex 0000000..8da3b25[m
[1m--- /dev/null[m
[1m+++ b/project/plugins.sbt[m
[36m@@ -0,0 +1,8 @@[m
[32m+[m[32m// Comment to get more information during initialization[m
[32m+[m[32mlogLevel := Level.Warn[m
[32m+[m
[32m+[m[32m// The Typesafe repository[m
[32m+[m[32mresolvers += "Typesafe repository" at "http://repo.typesafe.com/typesafe/releases/"[m
[32m+[m
[32m+[m[32m// Use the Play sbt plugin for Play projects[m
[32m+[m[32maddSbtPlugin("com.typesafe.play" % "sbt-plugin" % "2.2.6")[m
\ No newline at end of file[m
[1mdiff --git a/public/images/favicon.png b/public/images/favicon.png[m
[1mnew file mode 100644[m
[1mindex 0000000..c7d92d2[m
Binary files /dev/null and b/public/images/favicon.png differ
[1mdiff --git a/public/javascripts/jquery-1.9.0.min.js b/public/javascripts/jquery-1.9.0.min.js[m
[1mnew file mode 100644[m
[1mindex 0000000..50d1b22[m
[1m--- /dev/null[m
[1m+++ b/public/javascripts/jquery-1.9.0.min.js[m
[36m@@ -0,0 +1,4 @@[m
[