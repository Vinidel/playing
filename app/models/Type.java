package models;

import java.util.*;
import play.data.validation.Constraints.*;
import play.db.ebean.*;

import javax.persistence.*;

  @Entity
  public class Type extends Model{

      @Id
      public Long id;
      @Required
      public String Name;

  public static Finder<Long,Type> find = new Finder(
        Long.class, Task.class
  );

  public static List<Type> all(){
    return find.all();
  }

  public static void create(Type type){
    type.save();
  }

  public static void delete(Long id){
    find.ref(id).delete();
  }



  }
