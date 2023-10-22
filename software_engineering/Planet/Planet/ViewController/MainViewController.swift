//
//  ViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/15.
//

import UIKit
import SnapKit

let screen_width = UIScreen.main.bounds.width
let screen_height = UIScreen.main.bounds.height

class MainViewController: UIViewController {
    
    var profile = UIButton()
    var userName = UIButton()
    
    var planetView = UIImageView()
    var diaryBtn = UIButton()
    var musicBtn = UIButton()
    
    var homeToMoodBtn = UIButton()

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        setupUserInformation()
        setupPlanet()
        setupHomeToMood()
        NotificationCenter.default.addObserver(self, selector: #selector(changeUserInfo), name: .init(rawValue: "login success"), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(exitLogin), name: .init(rawValue: "exit"), object: nil)
    }
    
    @objc func exitLogin(){
        setupInfo()
    }
    
    @objc func changeUserInfo(){
        DispatchQueue.main.async {
            self.userName.setTitle(UserDefaults.standard.string(forKey: "userName"), for: .normal)
            let profileImg = UIImage(data: UserDefaults.standard.data(forKey: "profile")!)
            self.profile.setImage(profileImg, for: .normal)
        }
    }
    
    private func notLoginAlert(){
        let alertView = UIAlertController.init(title: "提示", message: "还没有登录喔，请先登录再使用叭", preferredStyle: .alert)
        let alert = UIAlertAction.init(title: "确定", style: .default) { (UIAlertAction) in
            
        }
        alertView.addAction(alert)
        self.present(alertView, animated: true, completion: nil)
    }
    
    private func setupInfo(){
        var image:UIImage
        if let _ = UserDefaults.standard.string(forKey: "userName") {
            let data = UserDefaults.standard.data(forKey: "profile")
            image = UIImage(data: data!)!
        }else{
            image = UIImage(named: "user")!
        }
        profile.setImage(image, for: .normal)
        
        var title:String
        if let text = UserDefaults.standard.string(forKey: "userName") {
            title = text
        }else{
            title = "User"
        }
        userName.setTitle(title, for: .normal)
    }
    
    private func setupUserInformation(){
        setupInfo()
        self.view.addSubview(profile)
        profile.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(30)
            make.top.equalToSuperview().offset(100)
            make.width.height.equalTo(50)
        }
        profile.layer.masksToBounds = true
        profile.layer.cornerRadius = 6
        self.view.addSubview(userName)
        userName.snp.makeConstraints { make in
            make.left.equalTo(profile.snp.right).offset(20)
            make.centerY.equalTo(profile.snp.centerY)
        }
        profile.addTarget(self, action: #selector(goToInfo), for: .touchUpInside)
        userName.addTarget(self, action: #selector(goToInfo), for: .touchUpInside)
    }
    
    @objc func goToInfo(){
        if let _ = UserDefaults.standard.string(forKey: "userName") {
            let vc = InfoViewController()
            vc.modalPresentationStyle = .fullScreen
            self.present(vc, animated: true, completion: nil)
        }else{
            let vc = LoginViewController()
            vc.modalPresentationStyle = .fullScreen
            self.present(vc, animated: true, completion: nil)
        }
    }
    
    private func setupPlanet(){
        self.view.addSubview(planetView)
        planetView.isUserInteractionEnabled = true
        planetView.image = UIImage(named: "planet")
        let mutiply = planetView.image!.size.height / planetView.image!.size.width
        planetView.snp.makeConstraints { make in
            make.centerX.equalToSuperview()
            make.centerY.equalToSuperview().offset(-90)
            make.width.equalToSuperview().multipliedBy(0.90)
            make.height.equalTo(planetView.snp.width).multipliedBy(mutiply)
        }
        
        self.view.addSubview(diaryBtn)
        diaryBtn.setImage(UIImage(named: "diary"), for: .normal)
        diaryBtn.snp.makeConstraints { make in
            make.left.equalTo(planetView.snp.left).offset(80)
            make.top.equalTo(planetView.snp.bottom).offset(30)
            make.width.height.equalTo(60)
        }
        diaryBtn.addTarget(self, action: #selector(goToDiary), for: .touchUpInside)
        
        self.view.addSubview(musicBtn)
        musicBtn.setImage(UIImage(named: "music"), for: .normal)
        musicBtn.snp.makeConstraints { make in
            make.right.equalTo(planetView.snp.right).offset(-80)
            make.top.equalTo(planetView.snp.bottom).offset(30)
            make.width.height.equalTo(60)
        }
        musicBtn.addTarget(self, action: #selector(goToMusic), for: .touchUpInside)
    }
    
    @objc func goToDiary(){
        if let _ = UserDefaults.standard.string(forKey: "userName") {
            let vc = CreateDiaryViewController()
            vc.modalPresentationStyle = .fullScreen
            self.present(vc, animated: true, completion: nil)
        }else{
            self.notLoginAlert()
        }
    }
    
    @objc func goToMusic(){
        if let _ = UserDefaults.standard.string(forKey: "userName") {
            let vc = RecommendMusicViewController()
            vc.modalPresentationStyle = .fullScreen
            self.present(vc, animated: true, completion: nil)
        }else{
            self.notLoginAlert()
        }
    }
    
    private func setupHomeToMood(){
        self.view.addSubview(homeToMoodBtn)
        homeToMoodBtn.backgroundColor = UIColor(red:21/255.0, green: 85/255.0, blue: 154/255.0, alpha: 1.0)
        homeToMoodBtn.layer.masksToBounds = true
        homeToMoodBtn.layer.cornerRadius = 40
        homeToMoodBtn.layer.borderColor = CGColor.init(red: 199/255.0, green: 210/255.0, blue: 212/255.0, alpha: 1)
        homeToMoodBtn.layer.borderWidth = 8
        homeToMoodBtn.snp.makeConstraints { make in
            make.width.height.equalTo(80)
            make.bottom.equalToSuperview().offset(-100)
            make.centerX.equalToSuperview()
        }
        homeToMoodBtn.addTarget(self, action: #selector(goToMoodSelect), for: .touchUpInside)
    }
    
    @objc func goToMoodSelect(){
        if let _ = UserDefaults.standard.string(forKey: "userName") {
            let vc = SelectMoodViewController()
            vc.modalPresentationStyle = .fullScreen
            self.present(vc, animated: true, completion: nil)
        }else{
            self.notLoginAlert()
        }
    }
}

