package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.*;

import java.io.*;
import java.util.*;

/**
 * AbstractIndex的具体实现类
 */
public class Index extends AbstractIndex {
    /**
     * 返回索引的字符串表示
     *
     * @return 索引的字符串表示
     */
    @Override
    public String toString() {
        StringBuffer str = new StringBuffer();
        for(Map.Entry<Integer, String> entry:docIdToDocPathMapping.entrySet()){
            Integer mapKey = entry.getKey();
            String mapValue = entry.getValue();
            str.append(mapKey+":"+mapValue+"\n");
        }
        str.append("\n");
        for (Map.Entry<AbstractTerm, AbstractPostingList> entry:this.termToPostingListMapping.entrySet()){
            AbstractTerm term = entry.getKey();
            AbstractPostingList postingList = entry.getValue();
            str.append(term.toString()+"\n"+postingList.toString());
        }
        return str.toString();
    }

    /**
     * 添加文档到索引，更新索引内部的HashMap
     *
     * @param document ：文档的AbstractDocument子类型表示
     */
    @Override
    public void addDocument(AbstractDocument document) {
        //把该文档信息加入docIdToDocPathMapping
        docIdToDocPathMapping.put(document.getDocId(),document.getDocPath());
        //对文档中的三元组进行遍历加入termToPostingListMapping
        for (AbstractTermTuple termTuple:document.getTuples()){
            //判断当前termToPostingListMapping是否包含此单词
            if(termToPostingListMapping.containsKey(termTuple.term)){
                AbstractPostingList curPostingList = termToPostingListMapping.get(termTuple.term);
                //判断该词汇对应的PostingList是否包含该文件的Posting
                if(curPostingList.indexOf(document.getDocId())==-1){
                    //不包含该文件的Posting，创造一个Posting加入当前PostingList中
                    AbstractPosting curPosting = new Posting();
                    curPosting.setFreq(termTuple.freq);
                    curPosting.setDocId(document.getDocId());
                    curPosting.getPositions().add(termTuple.curPos);
                    curPostingList.add(curPosting);
                }else {
                    //包含该文件的Posting，在该Posting中加入当前三元组对应的位置
                    AbstractPosting curPosting = curPostingList.get(curPostingList.indexOf(document.getDocId()));
                    curPosting.getPositions().add(termTuple.curPos);
                    int freq = curPosting.getFreq();
                    curPosting.setFreq(freq+1);
                }
            }else {
                //当前termToPostingListMapping不包含此单词，构建当前词汇和PostingList的映射并加入Map中
                AbstractPosting posting = new Posting();
                posting.setDocId(document.getDocId());
                posting.setFreq(termTuple.freq);
                posting.getPositions().add(termTuple.curPos);
                AbstractPostingList postingList = new PostingList();
                postingList.add(posting);
                termToPostingListMapping.put(termTuple.term,postingList);
            }
        }
    }

    /**
     * <pre>
     * 从索引文件里加载已经构建好的索引.内部调用FileSerializable接口方法readObject即可
     * @param file ：索引文件
     * </pre>
     */
    @Override
    public void load(File file) {
        try(ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(file))){
            this.docIdToDocPathMapping = (Map<Integer, String>) (inputStream.readObject());
            this.termToPostingListMapping = (Map<AbstractTerm,AbstractPostingList>)(inputStream.readObject());
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    /**
     * <pre>
     * 将在内存里构建好的索引写入到文件. 内部调用FileSerializable接口方法writeObject即可
     * @param file ：写入的目标索引文件
     * </pre>
     */
    @Override
    public void save(File file) {
        try(ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream(file))){
            outputStream.writeObject(this.docIdToDocPathMapping);
            outputStream.writeObject(this.termToPostingListMapping);
        }catch (FileNotFoundException e){
            e.printStackTrace();
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    /**
     * 返回指定单词的PostingList
     *
     * @param term : 指定的单词
     * @return ：指定单词的PostingList;如果索引字典没有该单词，则返回null
     */
    @Override
    public AbstractPostingList search(AbstractTerm term) {
        return this.termToPostingListMapping.get(term);
    }

    /**
     * 返回索引的字典.字典为索引里所有单词的并集
     *
     * @return ：索引中Term列表
     */
    @Override
    public Set<AbstractTerm> getDictionary() {
        return termToPostingListMapping.keySet();
    }

    /**
     * <pre>
     * 对索引进行优化，包括：
     *      对索引里每个单词的PostingList按docId从小到大排序
     *      同时对每个Posting里的positions从小到大排序
     * 在内存中把索引构建完后执行该方法
     * </pre>
     */
    @Override
    public void optimize() {
        for(AbstractPostingList value:termToPostingListMapping.values()){
            //先对PostingList排序
            value.sort();
            //再依次对PostingList中的每一个Posting的positions排序
            for (int i=0;i<value.size();i++){
                value.get(i).sort();
            }
        }
    }

    /**
     * 根据docId获得对应文档的完全路径名
     *
     * @param docId ：文档id
     * @return : 对应文档的完全路径名
     */
    @Override
    public String getDocName(int docId) {
        if(this!=null){
            return this.docIdToDocPathMapping.get(docId);
        }else return null;
    }

    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(docIdToDocPathMapping);
            out.writeObject(termToPostingListMapping);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 从二进制文件读
     *
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        try {
            this.docIdToDocPathMapping = (Map<Integer, String>) in.readObject();
            this.termToPostingListMapping = (Map<AbstractTerm, AbstractPostingList>) in.readObject();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
