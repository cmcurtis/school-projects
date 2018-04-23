package gui;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.text.MaskFormatter;

import individual.IndividualDatabase;
import individual.Provider;

import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class ProviderLogin {

  private JFrame frmProviderlogin;

  private IndividualDatabase dB;
  /**
   * Launch the application.
   */
  public static void newLogin() {
    EventQueue.invokeLater(new Runnable() {
      public void run() {
        try {
          ProviderLogin window = new ProviderLogin();
          window.frmProviderlogin.setVisible(true);
        } catch (Exception e) {
          e.printStackTrace();
        }
      }
    });
  }

  /**
   * Create the application.
   */
  public ProviderLogin() {
    initialize();
  }

  /**
   * Initialize the contents of the frame.
   */
  private void initialize() {
    frmProviderlogin = new JFrame();
    frmProviderlogin.setTitle("ProviderLogin");
    frmProviderlogin.setBounds(100, 100, 302, 192);
    frmProviderlogin.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frmProviderlogin.getContentPane().setLayout(null);
    
    JFormattedTextField frmtdtxtfldIdnumber = new JFormattedTextField(idFormatter("#########"));
    frmtdtxtfldIdnumber.setText("IdNumber");
    frmtdtxtfldIdnumber.setBounds(121, 46, 122, 20);
    frmProviderlogin.getContentPane().add(frmtdtxtfldIdnumber);
    
    JLabel lblEnterIdNumber = new JLabel("Enter ID Number:");
    lblEnterIdNumber.setBounds(10, 49, 101, 14);
    frmProviderlogin.getContentPane().add(lblEnterIdNumber);
    
    JButton btnLogin = new JButton("Login");
    btnLogin.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        String idNumber;
        try {
          idNumber = frmtdtxtfldIdnumber.getText();
          //Provider provider = dB.findProvider(idNumber);
          //if (provider != null) {
            frmProviderlogin.dispose();
          //}
          //else {
            //JOptionPane.showMessageDialog(null, "Invalid ID Number");
          //}
        }catch(Exception ex) {
            JOptionPane.showMessageDialog(null, "Invalid ID Number");
        }
        
      }
    });
    btnLogin.setBounds(131, 77, 89, 23);
    frmProviderlogin.getContentPane().add(btnLogin);
  }
  
  MaskFormatter idFormatter (String s){
    MaskFormatter formatter = null;
    try {
        formatter = new MaskFormatter(s);
    } catch (java.text.ParseException exc) {
        System.err.println("formatter is bad: " + exc.getMessage());
        System.exit(-1);
    }
    return formatter;
  }
}
