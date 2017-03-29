/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.net.ServerSocket;

/**
 *
 * @author user1
 */
public class Main {
    
    private static ServerSocket ss;
    
    public static void main(String[] args)
    {
        try{
            ss = new ServerSocket(4321);
            while(true){
                System.out.println("WAITING FOR CONNECTION...");
                new ServiceThread(ss.accept()).start();
                System.out.println("CLIENT CONNECTED...");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
}
