import java.sql.*;

public class Transform {
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://127.0.0.1:3306/sparsedb?allowPublicKeyRetrieval=true&useUnicode=true&characterEncoding=UTF8&useSSL=false&serverTimezone=UTC";
    static final String USER = "root";
    static final String PASS = "123123";
    /**
     * 向sc表中插入数据
     *
     */
    public static int insertSC(Connection connection,int sno,String col_name,String col_value){
        PreparedStatement statement = null;
        try {
            //String value = String.valueOf(col_value);
            String sql = "insert sc values(?,?,?);";
            statement = connection.prepareStatement(sql);
            statement.setInt(1,sno);
            statement.setString(2,col_name);
            statement.setString(3,col_value);
            int n = statement.executeUpdate();
            return n;
         }catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            try {
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try{
            Class.forName(JDBC_DRIVER);
            connection = DriverManager.getConnection(DB_URL, USER, PASS);
            statement = connection.createStatement();
            String SQL_str = "select * from entrance_exam;";
            resultSet = statement.executeQuery(SQL_str);
            while (resultSet.next()) {
                int sno = resultSet.getInt("sno");
                if(resultSet.getString("chinese")!=null){
                    insertSC(connection,sno,"chinese",resultSet.getString("chinese"));
                }
                if(resultSet.getString("math")!=null){
                    insertSC(connection,sno,"math",resultSet.getString("math"));
                }
                if(resultSet.getString("english")!=null){
                    insertSC(connection,sno,"english",resultSet.getString("english"));
                }
                if(resultSet.getString("physics")!=null){
                    insertSC(connection,sno,"physics",resultSet.getString("physics"));
                }
                if(resultSet.getString("chemistry")!=null){
                    insertSC(connection,sno,"chemistry",resultSet.getString("chemistry"));
                }
                if(resultSet.getString("biology")!=null){
                    insertSC(connection,sno,"biology",resultSet.getString("biology"));
                }
                if(resultSet.getString("history")!=null){
                    insertSC(connection,sno,"history",resultSet.getString("history"));
                }
                if(resultSet.getString("geography")!=null){
                    insertSC(connection,sno,"geography",resultSet.getString("geography"));
                }
                if(resultSet.getString("politics")!=null){
                    insertSC(connection,sno,"politics",resultSet.getString("politics"));
                }
            }   
        }catch (ClassNotFoundException e) {
            System.out.println("Sorry,can`t find the JDBC Driver!"); 
            e.printStackTrace();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } finally {
            try {
                if (connection != null) {
                    connection.close();
                }
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
    }
}