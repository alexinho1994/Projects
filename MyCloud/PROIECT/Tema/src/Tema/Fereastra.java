package Tema;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileWriter;
import java.util.StringTokenizer;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class Fereastra {
	
	public Director home;
	public Director d1;
	public Useri list;
	JFrame terminal;
	JTextField comanda;
	JTextArea text;
	JPanel panel;
	JList list2;
	JTable table;
	
	public static void main(String args[]) throws Exception
	{
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Fereastra window = new Fereastra();
					window.terminal.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});

	}
	
	public Fereastra()
	{
		initialize();
	}
	
	public void initialize()
	{
		d1=new Director("home", false, false, "root");
		list=new Useri();
		home=d1;
		
		terminal =new JFrame("Terminal");
		terminal.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		terminal.setMinimumSize(new Dimension(800, 600));
		terminal.getContentPane().setBackground(Color.black);
		terminal.setResizable(false);
		
		comanda=new JTextField();
		comanda.setSize(800, 20);
		comanda.setBackground(Color.black);
		comanda.setForeground(Color.white);
		
		panel=new JPanel();
		panel.setSize(800, 540);
		panel.setBackground(Color.black);
		JScrollPane scr = new JScrollPane(panel);
        scr.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
		
		text=new JTextArea();
		text.setSize(800, 540);
		text.setBackground(Color.black);
		text.setForeground(Color.white);
		text.setText("*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*");
        text.setLineWrap(true);
        text.setWrapStyleWord(true);
        text.setVisible(true);
        text.setEditable(false);
		panel.add(text);
		
		terminal.add(comanda, BorderLayout.SOUTH);
		terminal.add(scr, BorderLayout.CENTER);
		comanda.addActionListener(new ActionListener()
				{
					public void actionPerformed(ActionEvent arg0) {
						int ok=0;
						String com=comanda.getText();
						if(com.contains("-POO"))
						{
							ok=1;
							int index=com.indexOf(" -POO");
							String substr;
							substr=com.substring(0, index);
							substr=substr+com.substring(index+5);
							com=substr;
						}
						Output.setOutput("");
						CommandFactory a=new CommandFactory();
						Command c1=a.getCommand(com, list, home, d1);
						d1=c1.execute(d1);
						if(d1.getNume().equals("home"))
							home=d1;
						text=new JTextArea();
						text.setSize(750, 1);
						text.setBackground(Color.black);
						text.setForeground(Color.white);
						text.setLineWrap(true);
				        text.setWrapStyleWord(true);
				        text.setVisible(true);
				        text.setEditable(false);
				        panel.add(text);
						text.setText(">"+com);
						if(ok==0)
						text.setText(text.getText()+"\n"+"<"+Output.getOutput());
						if(ok==1)
						{
							if(com.startsWith("userinfo"))
							{
								DefaultListModel model=new DefaultListModel();
								StringTokenizer st=new StringTokenizer(Output.getOutput(), " ");
								while(st.hasMoreTokens())
									model.addElement(st.nextToken());
								list2=new JList(model);
								panel.add(list2);
							}
							if(com.startsWith("echo"))
							{
								Window parentWindow = SwingUtilities.windowForComponent(text);
				                JDialog dialog = new JDialog(parentWindow, "echo");
				                dialog.setLayout(new FlowLayout());
				                JLabel eticheta=new JLabel(Output.getOutput());
				                dialog.add(eticheta);
				                dialog.pack();
				                dialog.setVisible(true);

							}
							if(com.startsWith("ls"))
							{
								int dim=Output.getOutput().split("\n").length;
								Object columnNames[] = { "Tip", "Nume", "Dimensiuni", "Creat", "Permisiuni"};
								String rowData[][]=new String[dim][5];
								int i=0;
								StringTokenizer st=new StringTokenizer(Output.getOutput(), "\n");
								while(st.hasMoreTokens())
								{
									StringTokenizer st2=new StringTokenizer(st.nextToken(), " ");
									int j=0;
									while(st2.hasMoreTokens())
									{
										rowData[i][j]=st2.nextToken();
										j++;
									}
									i++;
								}
								table=new JTable(rowData, columnNames);
								panel.add(table);
							}
						}
						comanda.setText("");
					}
			
				});
		terminal.show();
		terminal.pack();
	}
	
}
