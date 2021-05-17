package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

/**
 * LengthTermTupleFilter是AbstractTermTupleFilter的具体子类，实现对单词长度的过滤
 */
public class LengthTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public LengthTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
        this.input = input;
    }
    /**
     * 获得下一个三元组。如果遇到单词长度不符合的三元组则跳过，递归得到下一个三元组。
     * @return ：下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple cur = input.next();
        if(cur!=null){
            int length = cur.term.getContent().length();
            //判断当前的得到的三元组长度是否匹配
            if (length<=Config.TERM_FILTER_MAXLENGTH && length>=Config.TERM_FILTER_MINLENGTH){
                return cur;
            }else {
                //若长度不匹配则递归调用直至找到或到三元组流末尾
                return this.next();
            }
        }else {
            return null;
        }
    }
}
