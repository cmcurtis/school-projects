package gui;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.text.MaskFormatter;

import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.layout.RowSpec;

import billChocAn.BillChocAn;
import directoryEntry.DirectoryEntry;
import servicesList.ServicesList;

import com.jgoodies.forms.layout.FormSpecs;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JFormattedTextField;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.awt.event.ActionEvent;
import java.awt.Font;

public class BillingForm extends JFrame {

  private JPanel contentPane;

  /**
   * Launch the application.
   */
  public static void submitForBilling() {
    EventQueue.invokeLater(new Runnable() {
      public void run() {
        try {
          BillingForm frame = new BillingForm();
          frame.setVisible(true);
        } catch (Exception e) {
          e.printStackTrace();
        }
      }
    });
  }

  /**
   * Create the frame.
   */
  public BillingForm() {
    setTitle("Billing Form");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setBounds(100, 100, 450, 300);
    contentPane = new JPanel();
    contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
    setContentPane(contentPane);
    contentPane.setLayout(new FormLayout(new ColumnSpec[] {
        FormSpecs.RELATED_GAP_COLSPEC,
        FormSpecs.DEFAULT_COLSPEC,
        FormSpecs.RELATED_GAP_COLSPEC,
        FormSpecs.DEFAULT_COLSPEC,
        FormSpecs.RELATED_GAP_COLSPEC,
        ColumnSpec.decode("default:grow"),},
      new RowSpec[] {
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,
        FormSpecs.RELATED_GAP_ROWSPEC,
        FormSpecs.DEFAULT_ROWSPEC,}));
    
    JLabel lblNewLabel = new JLabel("Provider Number:");
    lblNewLabel.setFont(new Font("Tahoma", Font.PLAIN, 12));
    contentPane.add(lblNewLabel, "2, 4");
    
    JFormattedTextField frmtdtxtfldProviderNum = new JFormattedTextField(idNumFormatter("#########"));
    frmtdtxtfldProviderNum.setText("Provider Num");
    contentPane.add(frmtdtxtfldProviderNum, "6, 4, fill, default");
    
    JLabel lblDateOfService = new JLabel("Date of Service: ");
    contentPane.add(lblDateOfService, "2, 8");
    
    JFormattedTextField frmtdtxtfldDOS = new JFormattedTextField(dosFormatter("##-##-####"));
    frmtdtxtfldDOS.setText("MM-DD-YYYY");
    contentPane.add(frmtdtxtfldDOS, "6, 8, fill, default");
    
    JLabel lblMemberNumber = new JLabel("Member Number:");
    contentPane.add(lblMemberNumber, "2, 10");
    
    JFormattedTextField frmtdtxtfldMemberNum = new JFormattedTextField(idNumFormatter("#########"));
    frmtdtxtfldMemberNum.setText("Member Num");
    contentPane.add(frmtdtxtfldMemberNum, "6, 10, fill, default");
    
    JLabel lblServiceCode = new JLabel("Service Code:");
    contentPane.add(lblServiceCode, "2, 12");
    
    JFormattedTextField frmtdtxtfldDigits = new JFormattedTextField(serviceCodeFormatter("######"));
    frmtdtxtfldDigits.setText("6 digits");
    contentPane.add(frmtdtxtfldDigits, "6, 12, fill, default");
    
    JLabel lblComments = new JLabel("Comments:");
    contentPane.add(lblComments, "2, 14");
    
    JFormattedTextField frmtdtxtfldEnterComments = new JFormattedTextField();
    frmtdtxtfldEnterComments.setText("enter comments (100 ch)");
    contentPane.add(frmtdtxtfldEnterComments, "6, 14, fill, default");
    
    JButton btnSubmit = new JButton("Submit");
    btnSubmit.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        String currentDate, dateOfService, providerID, memberID, serviceCode, comments;
        
        DateFormat dateFormat = new SimpleDateFormat("MM-dd-yyyy HH:mm:ss");
        Date date = new Date();
        
        currentDate = dateFormat.format(date);
        dateOfService = frmtdtxtfldDOS.getText();
        providerID = frmtdtxtfldProviderNum.getText();
        memberID = frmtdtxtfldMemberNum.getText();
        serviceCode = frmtdtxtfldDigits.getText();
        comments = frmtdtxtfldEnterComments.getText();
       
        //DirectoryEntry service = ServicesList.findService(serviceCode);
        //String serviceName = service.getServiceName();
        //if(serviceCode is incorrect) {
          //JOptionPane.showMessageDialog(null, "Invalid Service Code");
        //}
        //else {
            //double serviceFee = service.getServiceFee();
            //BillChocAn.billChocAn(currentDate, dateOfService, providerID, memberID, serviceCode, comments, FILE?);
            JOptionPane.showMessageDialog(null, "Service Fee: ");
            contentPane.setVisible(false);
        // }
      }
    });
    contentPane.add(btnSubmit, "6, 16");
  }
  
  MaskFormatter dosFormatter (String s){
    MaskFormatter formatter = null;
    try {
        formatter = new MaskFormatter(s);
    } catch (java.text.ParseException exc) {
        System.err.println("formatter is bad: " + exc.getMessage());
        System.exit(-1);
    }
    return formatter;
  }
  
  MaskFormatter idNumFormatter (String s){
    MaskFormatter formatter = null;
    try {
        formatter = new MaskFormatter(s);
    } catch (java.text.ParseException exc) {
        System.err.println("formatter is bad: " + exc.getMessage());
        System.exit(-1);
    }
    return formatter;
  }
  
  MaskFormatter serviceCodeFormatter (String s){
    MaskFormatter formatter = null;
    try {
        formatter = new MaskFormatter(s);
    } catch (java.text.ParseException exc) {
        System.err.println("formatter is bad: " + exc.getMessage());
        System.exit(-1);
    }
    return formatter;
  }
  
  MaskFormatter commentFormatter (String s){
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
