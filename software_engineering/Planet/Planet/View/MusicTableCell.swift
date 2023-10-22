//
//  MusicCollectionViewCell.swift
//  Planet
//
//  Created by ZouYa on 2021/12/22.
//

import UIKit

class MusicTableCell: UITableViewCell {
    
    static let identifier = "MusicTableCell"
    
    var label = UILabel()
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        self.backgroundColor = .clear
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    public func setupLabel(text:String){
        self.addSubview(label)
        label.text = text
        label.textAlignment = .center
        label.textColor = .white
        label.sizeToFit()
        label.snp.makeConstraints { make in
            make.center.equalToSuperview()
        }
    }
    
}
