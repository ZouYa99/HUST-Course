package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.parse.impl.LengthTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.PatternTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.StopWordTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.TermTupleScanner;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;

/**
 * DocumentBuilder是Document构造器的抽象父类AbstractDocumentBuilder的具体子类.
 */
public class DocumentBuilder extends AbstractDocumentBuilder {
    /**
     * <pre>
     * 由解析文本文档得到的TermTupleStream,构造Document对象.
     * @param docId             : 文档id
     * @param docPath           : 文档绝对路径
     * @param termTupleStream   : 文档对应的TermTupleStream
     * @return ：Document对象
     * </pre>
     */
    @Override
    public AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream) {
        AbstractDocument document = new Document(docId,docPath);
        //依次从三元组流中读取加入文档Document对象中
        AbstractTermTuple termTuple = new TermTuple();
        while ((termTuple = termTupleStream.next())!=null){
            document.addTuple(termTuple);
        }
        return document;
    }

    /**
     * <pre>
     * 由给定的File,构造Document对象.
     * 该方法利用输入参数file构造出AbstractTermTupleStream子类对象后,内部调用
     *      AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream)
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     * @param file      : 文档对应File对象
     * @return          : Document对象
     * </pre>
     */
    @Override
    public AbstractDocument build(int docId, String docPath, File file) {
        try {
            //将文件抽象成BufferedReader对象进行读取
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
            //传入TermTupleScanner，将文档转换成词汇三元组流
            AbstractTermTupleStream termTupleStream = new TermTupleScanner(reader);
            //装饰者模式：进行单词长度过滤
            AbstractTermTupleStream lengthFilter = new LengthTermTupleFilter(termTupleStream);
            //装饰者模式：进行模式过滤
            AbstractTermTupleStream patternFilter = new PatternTermTupleFilter(lengthFilter);
            //装饰者模式：进行停用词过滤
            AbstractTermTupleStream stopWordsFilter = new StopWordTermTupleFilter(patternFilter);
            //调用（复用）上一个重载build函数得到文件对象
            return build(docId,docPath,stopWordsFilter);
        }catch (java.io.FileNotFoundException e){
            e.printStackTrace();
        }
        return null;
    }
}
