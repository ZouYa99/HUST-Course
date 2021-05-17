package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * TermTupleScanner是AbstractTermTupleScanner的具体子类
 */
public class TermTupleScanner extends AbstractTermTupleScanner {

    private List<AbstractTermTuple> lists = new ArrayList<>();
    private int curIndex = 0;
    /**
     * 缺省构造函数
     */
    public TermTupleScanner(){}
    /**
     * 构造函数
     * @param input：指定输入流对象，应该关联到一个文本文件
     */
    public TermTupleScanner(BufferedReader input){
        this.input = input;
        //从input中读取所有内容
        String s = null;
        try{
            StringBuffer buf = new StringBuffer();
            while( (s = input.readLine()) != null){
                buf.append(s).append("\n"); //reader.readLine())返回的字符串会去掉换行符，因此这里要加上
            }
            s = buf.toString().trim(); //去掉最后一个多的换行符
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        //判断是否要忽略大小写，若要忽略则转化成小写
        if(Config.IGNORE_CASE)
            s = s.toLowerCase();
        //进行分词
        StringSplitter splitter = new StringSplitter();
        splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
        List<String> strings = splitter.splitByRegex(s);
        int pos = 0;
        //创建所有词汇的三元组list并保存为该类的实例数据成员，便于后续迭代读取
        for (String cur:strings){
            AbstractTermTuple termTuple = new TermTuple(cur,pos++);
            lists.add(termTuple);
        }
    }

    /**
     * 获得下一个三元组
     * @return ：下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        if(curIndex<lists.size()){
            //读取对应下一个数据并把控制变量加1
            return lists.get(curIndex++);
        }else{
            curIndex = 0;
            return null;
        }
    }
}
