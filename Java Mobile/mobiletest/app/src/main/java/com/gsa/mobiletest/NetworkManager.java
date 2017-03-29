package com.gsa.mobiletest;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * Created by user1 on 17/08/2016.
 */
public class NetworkManager {
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;

    private NetworkManager(){
        try{
            socket = new Socket("192.168.1.101", 4321);
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(
                    new InputStreamReader(
                            socket.getInputStream()));
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private static final class SingletonHolder{
        private static final NetworkManager SINGLETON = new NetworkManager();
    }

    public static NetworkManager getInstance(){
        return SingletonHolder.SINGLETON;
    }

    public void sendLoginCommand(){
        out.println("login");
    }

    public void sendRegisterCommand()  { out.println("register"); }

    public void sendCredentials(String username, String pass){
        out.println(username);
        out.println(pass);
    }

    public boolean isLoggedIn(){
        try {
            return in.readLine().equalsIgnoreCase("ok");
        }catch (IOException e){
            e.printStackTrace();
        }
        return false;
    }
}
