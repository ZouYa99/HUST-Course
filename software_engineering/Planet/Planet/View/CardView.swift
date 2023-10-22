//
//  CardView.swift
//  Planet
//
//  Created by ZouYa on 2021/12/20.
//

import UIKit

class CardView: UIView {
    
    var backgroundCard = UIImageView()
    var titleLabel = UILabel()
    var singerLabel = UILabel()
    var lyricsLabel:UITextView!
    var coverView = UIImageView()
    var favoriteBtn:UIButton!
    
    var id:Int = 0
    var title:String = ""
    var singer:String = ""
    var lyrics:String = ""
    var cover = UIImage()
    var coverStr:String = ""
    var type:String = ""
    var isFavorite:Bool = false
    
    override init(frame: CGRect) {
        super.init(frame: frame)
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }

    public func setup(title:String, singer:String,lyrics:String,cover:UIImage,id:Int,coverStr:String,type:String){
        self.title = title
        self.singer = singer
        self.lyrics = lyrics
        self.cover = cover
        self.id = id
        self.coverStr = coverStr
        self.type = type
        setupCard()
        self.isUserInteractionEnabled = true
        for view in self.subviews {
            view.isUserInteractionEnabled = true
        }
    }
    
    @objc func favoriteOrNot(){
        if isFavorite {
            sendNotFavorite()
        }else{
            sendFavorite()
        }
    }
    
    private func sendFavorite(){
        //IP是119.3.154.207，端口是8080
        print("post")
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/music/like", method: .post, parameter: nil)
        let user_id = UserDefaults.standard.string(forKey: "email")
        let music = Music(MusicID: id, MusicName: title, Singer: singer, Cover: coverStr, Lyric: lyrics, _Type: type)
        let postMusic = PostMusic(user_id: user_id!, music: music)
        let response = NetworkMgr.shared.request(API: webAPI, parameters: postMusic, headers: nil)
        response.responseDict { result in
            switch result {
            case .success(let model):
                print(model)
                let status = model["status"] as! Int
                if status == 1 {
                    DispatchQueue.main.async {
                        self.changeFavorite()
                    }
                }else{
                    
                }
            case .failure(_):
                break
            }
        }
    }
    
    
    private func sendNotFavorite(){
        //IP是119.3.154.207，端口是8080
        print("postFa")
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/music/like", method: .delete, parameter: nil)
        let user_id = UserDefaults.standard.string(forKey: "email")
        let delete = DeleteMusic(user_id: user_id!, music_code: id)
        print(delete)
        let response = NetworkMgr.shared.request(API: webAPI, parameters: delete, headers: nil)
        response.responseDict { result in
            switch result {
            case .success(let model):
                print(model)
                let status = model["status"] as! Int
                if status == 1 {
                    DispatchQueue.main.async {
                        self.changeFavorite()
                    }
                }else{
                    
                }
            case .failure(_):
                break
            }
        }
    }
    
    private func changeFavorite(){
        if isFavorite {
            isFavorite = false
            favoriteBtn.setImage(UIImage(named: "favorite_not"), for: .normal)
        }else{
            isFavorite = true
            favoriteBtn.setImage(UIImage(named: "favorite"), for: .normal)
        }
    }
    
    private func setupCard(){
        self.addSubview(backgroundCard)
        backgroundCard.image = UIImage(named: "card")
        backgroundCard.layer.masksToBounds = true
        backgroundCard.layer.cornerRadius = 18
        backgroundCard.snp.makeConstraints { make in
            make.center.equalToSuperview()
            make.width.height.equalToSuperview()
        }
        backgroundCard.isUserInteractionEnabled = true
        
        backgroundCard.addSubview(coverView)
        coverView.image = cover
        coverView.layer.masksToBounds = true
        coverView.layer.cornerRadius = 15
        coverView.snp.makeConstraints { make in
            make.top.equalToSuperview().offset(30)
            make.width.height.equalTo(120)
            make.left.equalToSuperview().offset(40)
        }
        
        backgroundCard.addSubview(titleLabel)
        titleLabel.text = title
        titleLabel.font = UIFont.systemFont(ofSize: 20)
        titleLabel.textColor = .black
        titleLabel.sizeToFit()
        titleLabel.snp.makeConstraints { make in
            make.top.equalToSuperview().offset(30)
            make.left.equalTo(coverView.snp.right).offset(20)
        }
        
        backgroundCard.addSubview(singerLabel)
        singerLabel.text = singer
        singerLabel.font = UIFont.systemFont(ofSize: 18)
        singerLabel.textColor = .black
        singerLabel.sizeToFit()
        singerLabel.snp.makeConstraints { make in
            make.top.equalTo(titleLabel.snp.bottom).offset(10)
            make.left.equalTo(coverView.snp.right).offset(20)
        }
        
        favoriteBtn = UIButton(frame: CGRect(x: 0, y: 0, width: 30, height: 30))
        backgroundCard.addSubview(favoriteBtn)
        if isFavorite {
            favoriteBtn.setImage(UIImage(named: "favorite"), for: .normal)
        }else{
            favoriteBtn.setImage(UIImage(named: "favorite_not"), for: .normal)
        }
        favoriteBtn.snp.makeConstraints { make in
            make.left.equalTo(coverView.snp.right).offset(40)
            make.top.equalTo(singerLabel.snp.bottom).offset(10)
            make.width.height.equalTo(30)
        }
        favoriteBtn.addTarget(self, action: #selector(favoriteOrNot), for: .touchUpInside)
        favoriteBtn.isUserInteractionEnabled = true
        print(favoriteBtn.frame)
        
        lyricsLabel = UITextView(frame: CGRect(x: 0, y: 0, width: 200, height: 300))
        backgroundCard.addSubview(lyricsLabel)
        lyricsLabel.textAlignment = .center
        lyricsLabel.textColor = .black
        lyricsLabel.text = lyrics
        lyricsLabel.backgroundColor = .clear
        lyricsLabel.contentMode = .top
        lyricsLabel.snp.makeConstraints { make in
            make.centerX.equalToSuperview()
            make.top.equalTo(coverView.snp.bottom).offset(20)
            make.width.equalToSuperview().multipliedBy(0.90)
            make.height.equalTo(280)
        }
        lyricsLabel.isEditable = false
        lyricsLabel.alwaysBounceVertical = true
        lyricsLabel.alwaysBounceHorizontal = false
        lyricsLabel.showsVerticalScrollIndicator = false
        lyricsLabel.showsHorizontalScrollIndicator = false
//        lyricsLabel.allowsEditingTextAttributes = false
        lyricsLabel.isUserInteractionEnabled = true
        lyricsLabel.contentOffset.y = -200
    }
}
