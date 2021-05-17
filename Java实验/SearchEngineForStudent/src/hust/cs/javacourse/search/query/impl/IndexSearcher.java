package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * IndexSearcher是AbstractIndexSearcher的具体子类
 */
public class IndexSearcher extends AbstractIndexSearcher {
    /**
     * 从指定索引文件打开索引，加载到index对象里. 一定要先打开索引，才能执行search方法
     * @param indexFile ：指定索引文件
     */
    @Override
    public void open(String indexFile) {
        this.index.load(new File(indexFile));
    }
    /**
     * 根据单个检索词进行搜索
     * @param queryTerm ：检索词
     * @param sorter ：排序器
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        List<AbstractHit> hitList = new ArrayList<AbstractHit>();
        for (Map.Entry<AbstractTerm, AbstractPostingList> entry:index.termToPostingListMapping.entrySet()){
            //遍历倒排索引，判断当前词汇是否为查询词
            if(entry.getKey().equals(queryTerm)){
                //找到查询词的PostingList，对应建立一个个Hit对象的并加入List中保存
                for (int i=0;i<entry.getValue().size();i++){
                    AbstractPosting curPosting = entry.getValue().get(i);
                    String path = index.docIdToDocPathMapping.get(curPosting.getDocId());
                    AbstractHit hit = new Hit(curPosting.getDocId(),path);
                    hit.getTermPostingMapping().put(entry.getKey(),curPosting);
                    hitList.add(hit);
                }
            }
        }
        //计算Hit对象的分数
        for (AbstractHit hit:hitList){
            sorter.score(hit);
        }
        //排序
        sorter.sort(hitList);
        //将List转化为数组返回
        AbstractHit[] hits = new Hit[hitList.size()];
        for (int i=0;i<hitList.size();i++){
            hits[i]=hitList.get(i);
        }
        return hits;
    }
    /**
     *
     * 根据二个检索词进行搜索
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter ：    排序器
     * @param combine ：   多个检索词的逻辑组合方式
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination combine) {
        List<AbstractHit> hitList = new ArrayList<AbstractHit>();
        //对两个检索词分别进行搜索得到命中数组
        AbstractHit[] hits1 = this.search(queryTerm1,sorter);
        AbstractHit[] hits2 = this.search(queryTerm2,sorter);
        if(combine == LogicalCombination.OR){
            //对其中一个数组直接加入全部命中
            for (AbstractHit hit1:hits1){
                hitList.add(hit1);
            }
            //遍历另一个数组
            for (AbstractHit hit2:hits2){
                AbstractHit thisHit = null;
                //对两个命中数组做一个合并，遍历查找hitList中是否包含该命中的相应文件id，因为Hit是通过docId来进行唯一性区分的
                for (AbstractHit curHit:hitList){
                    if(curHit.getDocId()==hit2.getDocId()){
                        thisHit=curHit;
                        break;
                    }
                }
                if(thisHit!=null){
                    //找到对应的hit，则直接在该hit中加入另一个词汇的信息即可
                    thisHit.getTermPostingMapping().putAll(hit2.getTermPostingMapping());
                }else {
                    //没有找到对应的hit，则直接加入
                    hitList.add(hit2);
                }
            }
        }else if(combine == LogicalCombination.AND){
            //若为与，则双重循环查找两个命中数组中都有的文件，建立新的命中对象加入命中数组
            for (AbstractHit hit1:hits1){
                for (AbstractHit hit2:hits2){
                    if(hit1.getDocId()==hit2.getDocId()){
                        AbstractHit hit = new Hit(hit1.getDocId(),hit1.getDocPath());
                        hit.getTermPostingMapping().putAll(hit1.getTermPostingMapping());
                        hit.getTermPostingMapping().putAll(hit2.getTermPostingMapping());
                        hitList.add(hit);
                    }
                }
            }
        }
        //计算Hit对象的分数
        for (AbstractHit hit:hitList){
            sorter.score(hit);
        }
        //排序
        sorter.sort(hitList);
        //将List转化为数组返回
        AbstractHit[] hits = new Hit[hitList.size()];
        for (int i=0;i<hitList.size();i++){
            hits[i]=hitList.get(i);
        }
        return hits;
    }
}
