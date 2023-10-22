import java.sql.*;
import java.util.Scanner;

public class Transfer {
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://127.0.0.1:3306/finance?allowPublicKeyRetrieval=true&useUnicode=true&characterEncoding=UTF8&useSSL=false&serverTimezone=UTC";
    static final String USER = "root";
    static final String PASS = "123123";
    /**
     * 转账操作
     *
     * @param connection 数据库连接对象
     * @param sourceCard 转出账号
     * @param destCard 转入账号
     * @param amount  转账金额
     * @return boolean
     *   true  - 转账成功
     *   false - 转账失败
     */
    public static boolean transferBalance(Connection connection,
    String sourceCard,String destCard, double amount){
        PreparedStatement statement = null;
        Statement se_statement = null;
        ResultSet resultSet = null;
        boolean flag = false;
        try{
            Class.forName(JDBC_DRIVER);
            connection = DriverManager.getConnection(DB_URL, USER, PASS);       
            se_statement = connection.createStatement();
            String sql_select_source = "select * from bank_card where b_number = "+"'"+sourceCard+"'"+";";
            resultSet = se_statement.executeQuery(sql_select_source);
            //转出账号不存在
            if(!resultSet.next()){
                return false;
            }
            //转出账号是信用卡
            if(resultSet.getString("b_type").equals("信用卡")){
                return false;
            }
            //转出账号余额不足
            if(resultSet.getInt("b_balance")<amount){
                return false;
            }
            String sql_select_desc = "select * from bank_card where b_number = "+"'"+destCard+"'"+";";
            resultSet = se_statement.executeQuery(sql_select_desc);
            //转入账号不存在
            if(!resultSet.next()){
                return false;
            }
            if(resultSet.getString("b_type").equals("信用卡")){
                flag = true;
            }
            //执行转出操作
            String sql_out = "update bank_card set b_balance = b_balance - ? where b_number = ?;";
            statement = connection.prepareStatement(sql_out);
            statement.setDouble(1,amount);
            statement.setString(2,sourceCard);
            statement.executeUpdate();
            //执行转入操作
            if(flag){
                String sql_in = "update bank_card set b_balance = b_balance - ? where b_number = ?;";
                statement = connection.prepareStatement(sql_in);
                statement.setDouble(1,amount);
                statement.setString(2,destCard);
                statement.executeUpdate();
            }else{
                String sql_in = "update bank_card set b_balance = b_balance + ? where b_number = ?;";
                statement = connection.prepareStatement(sql_in);
                statement.setDouble(1,amount);
                statement.setString(2,destCard);
                statement.executeUpdate();
            }
            return true;
        }catch (ClassNotFoundException e) {
            System.out.println("Sorry,can`t find the JDBC Driver!"); 
            e.printStackTrace();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            try {
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
        return false;
    }

    // 不要修改main() 
    public static void main(String[] args) throws Exception {

        Scanner sc = new Scanner(System.in);
        Class.forName(JDBC_DRIVER);

        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);

        while(sc.hasNext())
        {
            String input = sc.nextLine();
            if(input.equals(""))
                break;

            String[]commands = input.split(" ");
            if(commands.length ==0)
                break;
            String payerCard = commands[0];
            String  payeeCard = commands[1];
            double  amount = Double.parseDouble(commands[2]);
            if (transferBalance(connection, payerCard, payeeCard, amount)) {
              System.out.println("转账成功。" );
            } else {
              System.out.println("转账失败,请核对卡号，卡类型及卡余额!");
            }
        }
    }

}
