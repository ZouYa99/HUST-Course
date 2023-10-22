//
//  UIView+Scale.swift
//  Planet
//
//  Created by ZouYa on 2021/12/20.
//

import UIKit

extension UIView{
    
    public func animateScale(isIdentity:Bool,completion:(()->Void)? = nil){
        UIView.animate(withDuration: 0.6, animations: {
            var scale:CGFloat
            if isIdentity {
                scale = 1.3
            }else{
                scale = 1.0
            }
            self.layer.setAffineTransform(CGAffineTransform(scaleX: scale, y: scale))
        }){ (complete) in
            if isIdentity {
                self.animateScale(isIdentity: false, completion: completion)
            }else{
                self.animateScale(isIdentity: true, completion: completion)
            }
        }
    }
}


let musicsArr:[Music] = [Music(MusicID: 11, MusicName: "All Too Well", Singer: "Taylor Swift", Cover: "red", Lyric: "Cause there we are again on that \n Little town street\nYou almost ran the red cause you were lookin' over me\nWind in my hair, I was there\nI remember it all too well\nPhoto album on the counter\nYour cheeks were turning red\nYou used to be a little kid with glasses\nIn a twin sized bed\nAnd your mother's telling stories\nAbout you on the tee ball team\nYou taught me about your past\nThinking your future was me", _Type: "pop"),Music(MusicID: 12, MusicName: "freedom", Singer: "Anthony Hamilton/Elayna Boynton", Cover: "red", Lyric: "Well I am looking for freedom\nlooking for freedom\nAnd to find it, may take everything I have\nI know all too well it don’t come easy\nthe chains of the world they seem to movin tight\nI try to walk around it was stumbling so familiar\ntry to get up but the doubt is so strong\nthere’s gotta be a wind in my bones\nI’m looking for freedom\nlooking for freedom\nand to find it, cost me everything I have\nWell I’m looking for freedom\nI’m looking for freedom", _Type: "pop")]
