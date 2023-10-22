//
//  SelectMoodViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/19.
//

import UIKit

class SelectMoodViewController: UIViewController {
    
    var titleLabel = UILabel()
    var homeBtn = UIButton()
    
    var glad = BubbleButton()
    var split = BubbleButton()
    var waitingForSunny = BubbleButton()
    var daze = BubbleButton()
    var emo = BubbleButton()
    var positive = BubbleButton()
    var study = BubbleButton()
    var messAround = BubbleButton()
    var btnArray:[BubbleButton] = []

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        btnArray = [glad,split,waitingForSunny,daze,emo,positive,study,messAround]
        setupTitle()
        setupHomeBtn()
        setupMood()
    }
    
    private func initToAddAnimation(){
        if let moodArray = UserDefaults.standard.stringArray(forKey: "mood") {
            for btn in btnArray {
                for mood in moodArray {
                    if btn.title(for: .normal) == mood {
                        DispatchQueue.main.async {
                            btn.layer.add(ScaleAnimation(), forKey: "scale")
                        }
                        btn.isChoosed = true
                        break
                    }
                }
            }
        }
    }
    
    @objc func clickToChooseMood(_ btn:BubbleButton){
        if btn.isChoosed {
            btn.layer.removeAnimation(forKey: "scale")
            btn.isChoosed = false
        }else{
            btn.layer.add(ScaleAnimation(), forKey: "scale")
            btn.isChoosed = true
        }
    }
    
    private func setupMood(){
        self.view.addSubview(glad)
        glad.setBackgroundImage(UIImage(named: "bubble2"), for: .normal)
        glad.setTitle("美滋滋", for: .normal)
        glad.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(30)
            make.width.height.equalTo(140)
            make.top.equalToSuperview().offset(150)
        }
        glad.addTarget(self, action: #selector(clickToChooseMood(_:)), for: .touchUpInside)
        
        self.view.addSubview(split)
        split.setBackgroundImage(UIImage(named: "bubble1"), for: .normal)
        split.setTitle("裂开", for: .normal)
        split.snp.makeConstraints { make in
            make.right.equalToSuperview().offset(-30)
            make.width.height.equalTo(80)
            make.top.equalToSuperview().offset(130)
        }
        split.addTarget(self, action: #selector(clickToChooseMood(_:)), for: .touchUpInside)
        
        self.view.addSubview(waitingForSunny)
        waitingForSunny.setBackgroundImage(UIImage(named: "bubble2"), for: .normal)
        waitingForSunny.setTitle("等天晴", for: .normal)
        waitingForSunny.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(155)
            make.width.height.equalTo(100)
            make.top.equalToSuperview().offset(260)
        }
        waitingForSunny.addTarget(self, action: #selector(clickToChooseMood(_:)), for: .touchUpInside)
        
        self.view.addSubview(daze)
        daze.setBackgroundImage(UIImage(named: "bubble1"), for: .normal)
        daze.setTitle("发呆", for: .normal)
        daze.snp.makeConstraints { make in
            make.right.equalToSuperview().offset(-30)
            make.width.height.equalTo(120)
            make.top.equalToSuperview().offset(240)
        }
        daze.addTarget(self, action: #selector(clickToChooseMood(_:)), for: .touchUpInside)
        
        self.view.addSubview(emo)
        emo.setBackgroundImage(UIImage(named: "bubble1"), for: .normal)
        emo.setTitle("emo", for: .normal)
        emo.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(40)
            make.width.height.equalTo(90)
            make.top.equalToSuperview().offset(350)
        }
        emo.addTarget(self, action: #selector(clickToChooseMood(_:)), for: .touchUpInside)
        
        self.view.addSubview(positive)
        positive.setBackgroundImage(UIImage(named: "bubble2"), for: .normal)
        positive.setTitle("元气满满", for: .normal)
        positive.snp.makeConstraints { make in
            make.right.equalToSuperview().offset(-70)
            make.width.height.equalTo(130)
            make.top.equalToSuperview().offset(370)
        }
        positive.addTarget(self, action: #selector(clickToChooseMood(_:)), for: .touchUpInside)
        
        self.view.addSubview(study)
        study.setBackgroundImage(UIImage(named: "bubble2"), for: .normal)
        study.setTitle("沉迷学习", for: .normal)
        study.snp.makeConstraints { make in
            make.left.equalToSuperview().offset(30)
            make.width.height.equalTo(180)
            make.top.equalToSuperview().offset(490)
        }
        study.addTarget(self, action: #selector(clickToChooseMood(_:)), for: .touchUpInside)
        
        self.view.addSubview(messAround)
        messAround.setBackgroundImage(UIImage(named: "bubble1"), for: .normal)
        messAround.setTitle("摸鱼", for: .normal)
        messAround.snp.makeConstraints { make in
            make.right.equalToSuperview().offset(-40)
            make.width.height.equalTo(150)
            make.top.equalToSuperview().offset(530)
        }
        messAround.addTarget(self, action: #selector(clickToChooseMood(_:)), for: .touchUpInside)
        
        initToAddAnimation()
    }
    
    private func setupTitle(){
        self.view.addSubview(titleLabel)
        titleLabel.text = "选择你今天的心情"
        titleLabel.font = UIFont.systemFont(ofSize: 25)
        titleLabel.textColor = .white
        titleLabel.sizeToFit()
        titleLabel.snp.makeConstraints { make in
            make.top.equalToSuperview().offset(80)
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
        homeBtn.addTarget(self, action: #selector(confirmBubble), for: .touchUpInside)
    }
    
    @objc func confirmBubble(){
        var strArray:[String] = []
        for btn in btnArray{
            if btn.isChoosed {
                strArray.append(btn.title(for: .normal)!)
            }
        }
        UserDefaults.standard.set(strArray, forKey: "mood")
        sendToNetwork(strArray: strArray)
    }
    
    private func sendToNetwork(strArray:[String]){
        //IP是119.3.154.207，端口是8080
        print("post")
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/emotion/", method: .post, parameter: nil)
        let user_id = UserDefaults.standard.string(forKey: "userName")
        let emotion = Emotion(user_id: user_id!, emotions: strArray)
        let response = NetworkMgr.shared.request(API: webAPI, parameters: emotion, headers: nil)
        response.responseDict { result in
            switch result {
            case .success(let model):
                print(model)
                let status = model["status"] as! Int
                if status == 1 {
                    DispatchQueue.main.async {
                        self.goBack()
                    }
                }else{
                    DispatchQueue.main.async {
                        self.presentAlert()
                    }
                }
            case .failure(_):
                DispatchQueue.main.async {
                    self.presentAlert()
                }
                break
            }
        }
    }
    
    private func presentAlert(){
        let alertView = UIAlertController.init(title: "提示", message: "还没有选择心情，确定要离开吗", preferredStyle: .alert)
        let alert = UIAlertAction.init(title: "确定", style: .destructive) { (UIAlertAction) in
            self.goBack()
        }
        let cancel = UIAlertAction.init(title: "取消", style: .cancel, handler: nil)
        alertView.addAction(alert)
        alertView.addAction(cancel)
        self.present(alertView, animated: true, completion: nil)
    }
    
    private func goBack(){
        //释放当前页面
        self.dismiss(animated: true)
    }
    
}
