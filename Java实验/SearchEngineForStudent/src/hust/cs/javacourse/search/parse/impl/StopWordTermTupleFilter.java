package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.StopWords;

/**
 * StopWordTermTupleFilter是AbstractTermTupleFilter的具体子类，实现停用词的过滤
 */
public class StopWordTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public StopWordTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
        this.input = input;
    }

    /**
     * 遍历检查当前词汇是否为停用词
     * @param term ：当前词汇
     * @return： true表明当前term为停用词，false表明不是
     */
    private boolean containStopWord(String term){
        for (String str:StopWords.STOP_WORDS){
            if (str.equals(term)){
                return true;
            }
        }
        return false;
    }
    /**
     * 获得下一个三元组。如果遇到三元组单词是停用词中的一个，则跳过，递归得到下一个三元组。
     * @return ：下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple cur = input.next();
        if(cur!=null){
            //通过调用自定义的containStopWord方法，判断当前词汇是否为停用词
            if (containStopWord(cur.term.getContent())){
                //若为停用词，则递归调用直至找到不是停用词的词汇或到三元组末尾
                return this.next();
            }else {
                return cur;
            }
        }else return null;
    }
}
