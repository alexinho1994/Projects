package com.gsa.mobiletest;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    //private UserTask mAuthTask = null;
    private EditText txtUsername;
    private EditText txtParola;
    private Button btnLogin;
    private Button btnRegister;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initComponents();
        addEvents();
    }

    private void initComponents(){
        txtUsername = (EditText) findViewById(R.id.txtUser);
        txtParola = (EditText) findViewById(R.id.txtParola);
        btnLogin = (Button) findViewById(R.id.btnLogin);
        btnRegister = (Button) findViewById(R.id.btnRegister);
    }

    private void addEvents()
    {
        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String user = txtUsername.getText().toString();
                String pass = txtParola.getText().toString();


               /* mAuthTask = new UserTask(user, pass, "login");
                mAuthTask.execute((Void) null);*/


                    new NetworkAsyncTask(user, pass, "login", MainActivity.this).execute();


               /* if(NetworkManager.getInstance().isLoggedIn())
                {
                    Toast.makeText(MainActivity.this, "success", Toast.LENGTH_LONG).show();
                }
                else
                    Toast.makeText(MainActivity.this, "fail", Toast.LENGTH_LONG).show();*/
            }
        });

        btnRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String user = txtUsername.getText().toString();
                String pass = txtParola.getText().toString();

              /*  mAuthTask = new UserTask(user, pass, "register");
                mAuthTask.execute((Void) null);*/


                new NetworkAsyncTask(user, pass, "register", MainActivity.this).execute();


                /*if(NetworkManager.getInstance().isLoggedIn())
                {
                    Toast.makeText(MainActivity.this, "success", Toast.LENGTH_LONG).show();
                }
                else
                    Toast.makeText(MainActivity.this, "fail", Toast.LENGTH_LONG).show();*/
            }
        });
    }

    private class NetworkAsyncTask extends AsyncTask<Void, Void, Void>{

        private String user;
        private String pass;
        private String command;
        private Context context;
        private String ok;

        private NetworkAsyncTask(String user, String pass, String command, Context context)
        {
            this.user=user;
            this.command=command;
            this.pass=pass;
            this.context = context;
        }

        @Override
        protected Void doInBackground(Void... params) {
            if(command.equals("login"))
                 NetworkManager.getInstance().sendLoginCommand();
            else
                 NetworkManager.getInstance().sendRegisterCommand();
            NetworkManager.getInstance().sendCredentials(user, pass);
            if(NetworkManager.getInstance().isLoggedIn())
                ok = "ok";
            else
                ok = "nok";
            return null;
        }

        @Override
        protected void onPostExecute(Void aVoid) {
            super.onPostExecute(aVoid);
            if(ok.equals("ok")) {
                if (command.equals("register")) {
                    Toast.makeText(context, "succes", Toast.LENGTH_LONG).show();
                } else {
                    Intent intent = new Intent(context, Game.class);
                    context.startActivity(intent);
                    ((Activity) context).finish();
                }
            }
            else
                Toast.makeText(context, "esuat", Toast.LENGTH_LONG).show();
        }
    }
}


