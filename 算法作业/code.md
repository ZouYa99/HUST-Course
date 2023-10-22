```
//
//  ViewController.swift
//  Concentration
//
//  Created by ZouYa on 2021/11/19.
//

import UIKit

//屏幕宽度
var screen_width:CGFloat{
    return UIScreen.main.bounds.width
}
//自定义间隔
var spacing:CGFloat = 10

class ViewController: UIViewController {
    
    var titleLabel = UILabel()
    var collectionView:UICollectionView!
    
    //用于随机摆放图片
    var randomArray:[Int] = []
    //点击判断
    var indexForUp:IndexPath? = nil
    var matchCount:Int = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = .black
        
        let arr = [1,2,3,4,5,6,4,5,6,1,2,3]
        randomArray = arr.sorted { (_, _) -> Bool in
            arc4random() < arc4random()
        }
        print(randomArray)
        setupTitleLabel()
        setupCollectionView()
    }
    
    func setupTitleLabel(){
        self.view.addSubview(titleLabel)
        titleLabel.text = "Concentration"
        titleLabel.textAlignment = .center
        titleLabel.textColor = .white
        titleLabel.font = UIFont.systemFont(ofSize: 32)
        titleLabel.sizeToFit()
        titleLabel.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            titleLabel.topAnchor.constraint(equalTo: self.view.topAnchor, constant: 120),
            titleLabel.centerXAnchor.constraint(equalTo: self.view.centerXAnchor)
        ])
    }
    
    func setupCollectionView(){
        let flowLayout = UICollectionViewFlowLayout()
        
        let itemWidth = (screen_width - 30 - spacing*2)/3
        flowLayout.itemSize = CGSize(width: itemWidth, height: itemWidth)
        
        collectionView = UICollectionView(frame: .zero, collectionViewLayout: flowLayout)
        collectionView.delegate = self
        collectionView.dataSource = self
        view.addSubview(collectionView)
        collectionView.backgroundColor = .black
        collectionView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            collectionView.topAnchor.constraint(equalTo: titleLabel.bottomAnchor, constant: 50),
            collectionView.heightAnchor.constraint(equalToConstant: 500),
            collectionView.leadingAnchor.constraint(equalTo: self.view.leadingAnchor, constant: 15),
            collectionView.trailingAnchor.constraint(equalTo: self.view.trailingAnchor, constant: -15)
        ])
        
        collectionView.register(ConcentrationCell.self, forCellWithReuseIdentifier: ConcentrationCell.identifier)
    }

}

extension ViewController : UICollectionViewDelegate,UICollectionViewDataSource{

    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return 12
    }

    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: ConcentrationCell.identifier, for: indexPath) as! ConcentrationCell
        cell.configCellWithImage(image: UIImage(named: "p\(randomArray[indexPath.item]).jpg")!,tag: randomArray[indexPath.item])
        return cell
    }
    
    //点击调用的函数
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        let cell = collectionView.cellForItem(at: indexPath)
        let concentrationCell = cell as! ConcentrationCell
        if indexForUp == nil{
            concentrationCell.switchBack()
            indexForUp = indexPath
        }else if(indexForUp == indexPath){
            concentrationCell.switchBack()
            indexForUp = nil
        }else{
            let upCell = collectionView.cellForItem(at: indexForUp!)
            let upConcentrationCell = upCell as! ConcentrationCell
            concentrationCell.switchBack()
            DispatchQueue.main.asyncAfter(deadline: .now()+0.5) {
                if upConcentrationCell.tag == concentrationCell.tag {
                    self.matchCount+=1;
                    concentrationCell.match()
                    upConcentrationCell.match()
                    concentrationCell.isUserInteractionEnabled = false
                    upConcentrationCell.isUserInteractionEnabled = false
                    self.indexForUp = nil
                    if self.matchCount == 6 {
                        for cur in collectionView.visibleCells{
                            let concreteCell = cur as! ConcentrationCell
                            concreteCell.finishGames()
                        }
                    }
                }else{
                    concentrationCell.switchBack()
                    upConcentrationCell.switchBack()
                    self.indexForUp = nil
                }
            }
        }
    }

}


```



```
//
//  ConcentrationCell.swift
//  Concentration
//
//  Created by ZouYa on 2021/11/19.
//

import UIKit

class ConcentrationCell: UICollectionViewCell {
    
    static var identifier:String = "ConcentrationCell"
    
    var imageView = UIImageView()
    var image = UIImage()
    var isUp = false
    
    override init(frame: CGRect) {
        super.init(frame: frame)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    public func configCellWithImage(image:UIImage,tag:Int){
        self.image = image
        self.tag = tag
        setupUI()
    }
    
    public func switchBack(){
        if isUp {
            imageView.image = UIImage(named: "original.jpg")
            isUp = false
        }else{
            imageView.image = self.image
            isUp = true
        }
    }
    
    public func match(){
        imageView.image = UIImage(named: "victory.jpg")
    }
    
    public func finishGames(){
        imageView.image = UIImage(named: "congratulations.jpg")
    }
    
    private func setupUI(){
        addSubview(imageView)
        imageView.frame = CGRect(x: 0, y: 0, width: self.frame.width, height: self.frame.height)
        imageView.image = UIImage(named: "original.jpg")
        isUp = false
    }
}

```

