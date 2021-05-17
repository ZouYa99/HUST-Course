package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.FileUtil;

import java.io.File;
import java.util.Collections;
import java.util.List;

/**
 * IndexBuilder是索引构造器的抽象父类AbstractIndexBuilder的具体子类
 */
public class IndexBuilder extends AbstractIndexBuilder {
    /**
     * 构造函数
     * @param docBuilder：文档构造器
     */
    public IndexBuilder(AbstractDocumentBuilder docBuilder) {
        super(docBuilder);
    }
    /**
     * <pre>
     * 构建指定目录下的所有文本文件的倒排索引.
     *      需要遍历和解析目录下的每个文本文件, 得到对应的Document对象，再依次加入到索引，并将索引保存到文件.
     * @param rootDirectory ：指定目录
     * @return ：构建好的索引
     * </pre>
     */
    @Override
    public AbstractIndex buildIndex(String rootDirectory) {
        //得到该目录下的文件名
        List<String> fileNames = FileUtil.list(rootDirectory,".txt");
        Collections.sort(fileNames);//对文件名从小到大排序
        AbstractIndex index = new Index();
        //遍历所有文件名
        for (String filename:fileNames){
            //把文件构造成Document对象
            AbstractDocument document = docBuilder.build(docId++,filename,new File(filename));
            if(document!=null){
                //把当前文件加入倒排索引中
                index.addDocument(document);
            }
        }
        //倒排索引序列化到对应目录的对应文件中
        index.save(new File(Config.INDEX_DIR + "index.dat"));
        return index;
    }
}
