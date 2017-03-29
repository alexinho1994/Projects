package com.gsa.mobiletest;

import android.content.Intent;
import android.database.Cursor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.gsa.mobiletest.manager.DatabaseManager;

public class Game extends AppCompatActivity {

    private TextView intrebare;
    private Button raspuns1;
    private Button raspuns2;
    private Button raspuns3;
    private Button wiki;
    private Button next;
    private int id=1;
    private boolean corect=false;
    private DatabaseManager db;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);

        intrebare = (TextView) findViewById(R.id.intrebare);
        raspuns1 = (Button) findViewById(R.id.raspuns1);
        raspuns2 = (Button) findViewById(R.id.raspuns2);
        raspuns3 = (Button) findViewById(R.id.raspuns3);
        wiki = (Button) findViewById(R.id.wikipedia);
        next = (Button) findViewById(R.id.next);

        db = new DatabaseManager(Game.this);

        db.setDB();

        Cursor c = db.cautaIntrebare(id);
        intrebare.setText(c.getString(1));
        raspuns1.setText(c.getString(2));
        raspuns2.setText(c.getString(3));
        raspuns3.setText(c.getString(4));

        raspuns1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Cursor cv = db.cautaIntrebare(id);
                String rasp = cv.getString(5);
                if(rasp.equals(raspuns1.getText().toString())) {
                    corect = true;
                    Toast.makeText(Game.this, "Corect", Toast.LENGTH_LONG).show();
                }
                else
                    Toast.makeText(Game.this, "Gresit", Toast.LENGTH_LONG).show();
            }
        });

        raspuns2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Cursor cv = db.cautaIntrebare(id);
                String rasp = cv.getString(5);
                if(rasp.equals(raspuns2.getText().toString())) {
                    corect = true;
                    Toast.makeText(Game.this, "Corect", Toast.LENGTH_LONG).show();
                }
                else
                    Toast.makeText(Game.this, "Gresit", Toast.LENGTH_LONG).show();
            }
        });

        raspuns3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Cursor cv = db.cautaIntrebare(id);
                String rasp = cv.getString(5);
                if(rasp.equals(raspuns3.getText().toString())) {
                    corect = true;
                    Toast.makeText(Game.this, "Corect", Toast.LENGTH_LONG).show();
                }
                else
                    Toast.makeText(Game.this, "Gresit", Toast.LENGTH_LONG).show();
            }
        });

        next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(corect)
                {
                    if(id==6)
                    {
                        Intent intent = new Intent(Game.this, Finish.class);
                        startActivity(intent);
                        finish();
                    }
                    else {
                        id++;
                        Cursor cv = db.cautaIntrebare(id);
                        intrebare.setText(cv.getString(1));
                        raspuns1.setText(cv.getString(2));
                        raspuns2.setText(cv.getString(3));
                        raspuns3.setText(cv.getString(4));
                        corect = false;
                    }
                }
                else
                    Toast.makeText(Game.this, "Trebuie sa raspundeti corect pentru a merge mai departe", Toast.LENGTH_LONG).show();
            }
        });

        wiki.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(Game.this, Wikipedia.class);
                startActivity(intent);
            }
        });
    }
}
