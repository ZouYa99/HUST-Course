package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

import java.util.regex.Pattern;

/**
 * PatternTermTupleFilter是AbstractTermTupleFilter的具体子类，实现对单词模式的过滤
 */
public class PatternTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public PatternTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
        this.input = input;
    }
    /**
     * 获得下一个三元组。如果遇到单词模式不符合的三元组，则跳过，递归得到下一个三元组。
     * @return ：下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple cur = input.next();
        if(cur!=null){
            //判断当前得到的词汇是否匹配模式
            if (cur.term.getContent().matches(Config.TERM_FILTER_PATTERN)){
                return cur;
            }else {
                //不匹配则递归调用直至得到符合条件的三元组或到三元组末尾
                return this.next();
            }
        }else {
            return null;
        }
    }
}
