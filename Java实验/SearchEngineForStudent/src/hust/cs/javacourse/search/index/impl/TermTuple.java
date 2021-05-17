package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;

/**
 * TermTuple是AbstractTermTuple对象的具体子类.
 */
public class TermTuple extends AbstractTermTuple {
    /**
     * 缺省构造函数
     */
    public TermTuple(){};

    /**
     * 构造函数
     * @param termContent:词汇内容
     * @param curPos:词汇当前位置
     */
    public TermTuple(String termContent,int curPos){
        this.curPos = curPos;
        Term curTerm = new Term();
        curTerm.setContent(termContent);
        this.term = curTerm;
    }
    /**
     * 判断二个三元组内容是否相同
     * @param obj ：要比较的另外一个三元组
     * @return 如果内容相等（三个属性内容都相等）返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj) {
        if(obj instanceof TermTuple){
            TermTuple o = (TermTuple) obj;
            //比较三元组中的三个元素，同时相等时才为三元组相等
            return o.term.equals(this.term)&&this.freq==o.freq&&this.curPos==o.curPos;
        }else {
            return false;
        }
    }
    /**
     * 获得三元组的字符串表示
     * @return ： 三元组的字符串表示
     */
    @Override
    public String toString() {
        return this.term+"\nfrequency:"+this.freq+",current position:"+this.curPos+"\n";
    }
}
