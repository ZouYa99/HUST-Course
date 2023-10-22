//
//  ScaleAnimation.swift
//  Planet
//
//  Created by ZouYa on 2021/12/21.
//

import Foundation
import QuartzCore

class ScaleAnimation:CABasicAnimation{
    
    override init() {
        super.init()
        keyPath = "transform.scale"
        duration = 0.6
        repeatCount = .infinity
        autoreverses = true
        
        fromValue = 1.0
        toValue = 1.3
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
}
