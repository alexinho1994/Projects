/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Vector;

/**
 *
 * @author user1
 */
public class ServiceThread extends Thread{
    
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;
    private Vector<User> v;
            
    public ServiceThread(Socket socket) throws IOException{
        this.socket = socket;
        out = new PrintWriter(socket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        v = new Vector<User>();
    }
    
    @Override
    public void run(){
        try{
            while(true){
                System.out.println("WAITING FOR COMMAND...");
                String command = in.readLine();
                if(command == null) return;
                
                System.out.println("RECEIVED COMMAND "+command);
                if(command.equalsIgnoreCase("login")){
                    int ok = 0;
                    String username = in.readLine();
                    String pass = in.readLine();
                    System.out.println("RECEIVED USER AND PASS");
                    for(User u : v)
                    {
                        if(u.getUsername().equals(username) && u.getPassword().equals(pass))
                        {
                            ok = 1;
                            out.println("ok");
                        }
                    }
                    if(ok == 0)
                        out.println("nok");
                }
                
                if(command.equalsIgnoreCase("register"))
                {
                    String username = in.readLine();
                    String pass = in.readLine();
                    int ok=0;
                    for(User u: v)
                    {
                        if(u.getUsername().equals(username))
                            ok=1;
                    }
                    if(ok==0){
                        v.add(new User(username, pass));
                        out.println("ok");
                    }
                    else out.println("nok");
                }
                
                
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    
}
