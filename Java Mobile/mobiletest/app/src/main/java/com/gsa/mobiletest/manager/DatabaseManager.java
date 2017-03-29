package com.gsa.mobiletest.manager;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by user1 on 18/08/2016.
 */
public class DatabaseManager extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "intrebari.db";
    private static final int DATABASE_VERSION = 1;

    private static final String INTREBARI_TABLE = "intrebari";

    private SQLiteDatabase database;

    private static final String CREATE_INTREBARI_TABLE = "" +
            "CREATE TABLE intrebari (" +
            "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
            "intrebare TEXT NOT NULL," +
            "raspuns1 TEXT NOT NULL,"+
            "raspuns2 TEXT NOT NULL," +
            "raspuns3 TEXT NOT NULL," +
            "raspunscorect TEXT NOT NULL)";

    private static final String DROP_INTREBARI_TABLE = "" +
            "DROP TABLE IF EXISTS intrebari";

    public DatabaseManager(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(CREATE_INTREBARI_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL(DROP_INTREBARI_TABLE);
        onCreate(db);
    }

    public SQLiteDatabase open(){
        return getWritableDatabase();
    }

    public void setDB()
    {
        database = open();
        adaugaIntrebare("Cine a castigat UCL 2016?", "Real Madrid", "Barcelona", "Atletico Madrid", "Real Madrid");
        adaugaIntrebare("Cine a eliminat Barcelona?", "Real Madrid", "Atletico Madrid", "Manchester City", "Atletico Madrid");
        adaugaIntrebare("Cat a fost scorul finalei?", "3-1", "2-1", "1-1", "1-1");
        adaugaIntrebare("Cine a marcat penalty-ul decisiv?", "Ramos", "Benzema", "Ronaldo", "Ronaldo");
        adaugaIntrebare("Pe cine a eliminat Atletico Madrid in semifinale?", "Bayern", "City", "Barcelona", "Bayern");
        adaugaIntrebare("Cine a marcat golul lui Atletico?", "Carrasco", "Griezmann", "Torres", "Carrasco");
        close(database);
    }

    public void close(SQLiteDatabase db){
        db.close();
    }

    public long adaugaIntrebare(String intrebare,String raspuns1, String raspuns2, String raspuns3, String raspunscorect)
    {
        ContentValues cv = new ContentValues();
        cv.put("intrebare", intrebare);
        cv.put("raspuns1", raspuns1);
        cv.put("raspuns2", raspuns2);
        cv.put("raspuns3", raspuns3);
        cv.put("raspunscorect", raspunscorect);
        return database.insert(INTREBARI_TABLE, null, cv);
    }

    public Cursor cautaIntrebare(int id)
    {
        database = open();
        Cursor c =
                database.rawQuery("SELECT * FROM intrebari WHERE id = " + id, null);
        c.moveToFirst();
        return c;
    }
}
