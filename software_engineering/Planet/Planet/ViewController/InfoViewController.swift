//
//  InfoViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/19.
//

import UIKit
import SnapKit

class InfoViewController: UIViewController {
    
    var background = UIView()
    var profile = UIImageView()
    var nickname = UILabel()
    var email = UILabel()
    
    var favorite = UIImageView()
    var myFavorite = UIButton()
    
    var exitRegBtn = UIButton()
    var homeBtn = UIButton()

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        setupInfo()
        setupHomeBtn()
        setupFavorite()
    }
    
    @objc func gotoFavorite(){
        let vc = FavoriteMusicViewController()
        vc.modalPresentationStyle = .fullScreen
        self.present(vc, animated: true, completion: nil)
    }
    
    private func setupFavorite(){
        self.view.addSubview(favorite)
        favorite.image = UIImage(named: "favorite")
        favorite.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(80)
            make.width.height.equalTo(60)
            make.top.equalTo(background.snp.bottom).offset(120)
        }
        
        self.view.addSubview(myFavorite)
        myFavorite.backgroundColor = .white
        myFavorite.setTitle("我最喜欢的音乐", for: .normal)
        myFavorite.setTitleColor(.black, for: .normal)
        myFavorite.layer.masksToBounds = true
        myFavorite.layer.cornerRadius = 10
        myFavorite.snp.makeConstraints { make in
            make.left.equalTo(favorite.snp.right).offset(20)
            make.centerY.equalTo(favorite.snp.centerY)
            make.width.equalTo(150)
            make.height.equalTo(60)
        }
        myFavorite.addTarget(self, action: #selector(gotoFavorite), for: .touchUpInside)
        
        self.view.addSubview(exitRegBtn)
        exitRegBtn.setTitle("退出登录", for: .normal)
        exitRegBtn.setTitleColor(.white, for: .normal)
        exitRegBtn.backgroundColor = .darkGray
        exitRegBtn.layer.masksToBounds = true
        exitRegBtn.layer.cornerRadius = 15
        exitRegBtn.snp.makeConstraints { make in
            make.top.equalTo(myFavorite.snp.bottom).offset(50)
            make.centerX.equalToSuperview()
            make.width.equalTo(150)
            make.height.equalTo(50)
        }
        exitRegBtn.addTarget(self, action: #selector(exit), for: .touchUpInside)
    }
    
    @objc func exit(){
        clearAllUserDefaultsData()
        self.dismiss(animated: true, completion: nil)
        NotificationCenter.default.post(name: .init(rawValue: "exit"), object: nil)
    }
    
    private func clearAllUserDefaultsData(){
        let userDefaults = UserDefaults.standard
        let dics = userDefaults.dictionaryRepresentation()
        for key in dics {
            if key.key == "profile" {
                continue
            }
            userDefaults.removeObject(forKey: key.key)
        }
        userDefaults.synchronize()
    }
    
    private func setupInfo(){
        self.view.addSubview(background)
        background.backgroundColor = .white
        background.layer.masksToBounds = true
        background.layer.cornerRadius = 25
        background.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(20)
            make.right.equalToSuperview().offset(-20)
            make.top.equalToSuperview().offset(160)
            make.height.equalTo(220)
        }
        
        self.view.addSubview(profile)
        let data = UserDefaults.standard.data(forKey: "profile")
        profile.image = UIImage(data: data!)
        profile.layer.masksToBounds = true
        profile.layer.cornerRadius = 20
        profile.snp.makeConstraints { make in
            make.centerX.equalToSuperview()
            make.centerY.equalTo(background.snp.top)
            make.width.height.equalTo(120)
        }
        
        background.addSubview(nickname)
        nickname.text = UserDefaults.standard.string(forKey: "userName")
        nickname.textColor = .black
        nickname.font = UIFont.systemFont(ofSize: 25)
        nickname.sizeToFit()
        nickname.snp.makeConstraints { make in
            make.top.equalTo(profile.snp.bottom).offset(20)
            make.centerX.equalToSuperview()
        }
        
        background.addSubview(email)
        email.text = UserDefaults.standard.string(forKey: "email")
        email.textColor = .black
        email.font = UIFont.systemFont(ofSize: 20)
        email.sizeToFit()
        email.snp.makeConstraints { make in
            make.top.equalTo(nickname.snp.bottom).offset(30)
            make.centerX.equalToSuperview()
        }
    }
    
    private func setupHomeBtn(){
        self.view.addSubview(homeBtn)
        homeBtn.backgroundColor = UIColor(red:21/255.0, green: 85/255.0, blue: 154/255.0, alpha: 1.0)
        homeBtn.layer.masksToBounds = true
        homeBtn.layer.cornerRadius = 40
        homeBtn.layer.borderColor = CGColor.init(red: 199/255.0, green: 210/255.0, blue: 212/255.0, alpha: 1)
        homeBtn.layer.borderWidth = 8
        homeBtn.snp.makeConstraints { make in
            make.width.height.equalTo(80)
            make.bottom.equalToSuperview().offset(-100)
            make.centerX.equalToSuperview()
        }
        homeBtn.addTarget(self, action: #selector(goBack), for: .touchUpInside)
    }
    
    @objc func goBack(){
        //释放当前页面
        self.dismiss(animated: true)
    }

}
