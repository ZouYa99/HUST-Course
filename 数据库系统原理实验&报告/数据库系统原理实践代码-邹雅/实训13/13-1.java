/* 请在适当的位置补充代码，完成指定的任务 
   提示：
      try {


      } catch
    之间补充代码  
*/
import java.sql.*;

public class Client {
    public static void main(String[] args) {
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String URL = "jdbc:mysql://127.0.0.1:3306/finance?useUnicode=true&characterEncoding=UTF8&useSSL=false&serverTimezone=UTC";
            String USER = "root";
            String PASS = "123123";
            connection = DriverManager.getConnection(URL,USER,PASS);
            statement = connection.createStatement();
            String SQL_str = "select c_name,c_mail,c_phone from client where c_mail is not null;";
            resultSet = statement.executeQuery(SQL_str);
            System.out.print("姓名\t");
            System.out.print("邮箱\t\t\t\t");
            System.out.print("电话\n");
            while (resultSet.next()) {
                System.out.print(resultSet.getString("c_name"));
                System.out.print("\t");
                System.out.print(resultSet.getString("c_mail"));
                System.out.print("\t\t");
                System.out.print(resultSet.getString("c_phone"));
                System.out.print("\n");
            } 
 
         } catch (ClassNotFoundException e) {
            System.out.println("Sorry,can`t find the JDBC Driver!"); 
            e.printStackTrace();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            try {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (statement != null) {
                    statement.close();
                }

                if (connection != null) {
                    connection.close();
                }
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
    }
}
