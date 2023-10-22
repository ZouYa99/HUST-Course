//
//  DiaryCollectionCell.swift
//  Planet
//
//  Created by ZouYa on 2021/12/21.
//

import UIKit

class DiaryCollectionCell: UICollectionViewCell {
    
    static let identifier = "DiaryCollectionCell"
    
    var label = UILabel()
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        self.backgroundColor = .clear
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func setupUI(text:String){
        self.addSubview(label)
        label.textAlignment = .left
        label.text = text
        label.textColor = .black
        label.backgroundColor = .white
        label.font = UIFont.systemFont(ofSize: 22)
        label.numberOfLines = 0
        label.lineBreakMode = .byWordWrapping
        label.preferredMaxLayoutWidth = screen_width - 60
        label.sizeToFit()
        label.frame = CGRect(x: 30, y: 0, width: screen_width - 60, height: label.intrinsicContentSize.height + 20)
        label.layer.masksToBounds = true
        label.layer.cornerRadius = 8
    }
    
    func returnSize()->CGSize{
        return CGSize(width: screen_width, height: label.intrinsicContentSize.height + 20)
    }
}
