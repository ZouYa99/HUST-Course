//
//  DiaryViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/20.
//

import UIKit

class CreateDiaryViewController: UIViewController {
    
    var profile = UIImageView()
    var allBtn = UIButton()
    var sendBtn = UIButton()
    
    var tagField = UITextField()
    var textView = UITextView()
    
    var homeBtn = UIButton()

    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        // Do any additional setup after loading the view.
        textView.delegate = self
        tagField.delegate = self
        tagField.returnKeyType = .done
        setupProfile()
        setupTextView()
        setupFunctionBtn()
        setupHomeBtn()
    }
    
    private func checkIsEmpty(){
        if tagField.text?.count != 0 || textView.text.count != 0 {
            showAlert()
        }else{
            self.dismiss(animated: true, completion: nil)
        }
    }
    
    private func showAlert(){
        let alertView = UIAlertController.init(title: "提示", message: "还没有保存喔，真的要离开吗", preferredStyle: .alert)
        let alert = UIAlertAction.init(title: "确定", style: .destructive) { (UIAlertAction) in
            self.dismiss(animated: true, completion: nil)
        }
        let cancel = UIAlertAction.init(title: "取消", style: .cancel) { UIAlertAction in
        }
        alertView.addAction(alert)
        alertView.addAction(cancel)
        self.present(alertView, animated: true, completion: nil)

    }
    
    private func setupFunctionBtn(){
        self.view.addSubview(allBtn)
        allBtn.setTitle("查看全部", for: .normal)
        allBtn.backgroundColor = UIColor(red: 231/255.0, green: 124/255.0, blue: 142/255.0, alpha: 1)
        allBtn.setTitleColor(.black, for: .normal)
        allBtn.snp.makeConstraints { make in
            make.left.equalTo(profile.snp.right).offset(30)
            make.top.equalTo(profile.snp.top).offset(10)
            make.width.equalTo(80)
            make.height.equalTo(40)
        }
        allBtn.layer.masksToBounds = true
        allBtn.layer.cornerRadius = 8
        allBtn.addTarget(self, action: #selector(gotoAllDiary), for: .touchUpInside)
        
        self.view.addSubview(sendBtn)
        sendBtn.setTitle("发送日记", for: .normal)
        sendBtn.backgroundColor = .lightGray
        sendBtn.setTitleColor(.black, for: .normal)
        sendBtn.snp.makeConstraints { make in
            make.left.equalTo(allBtn.snp.right).offset(30)
            make.top.equalTo(profile.snp.top).offset(10)
            make.width.equalTo(80)
            make.height.equalTo(40)
        }
        sendBtn.layer.masksToBounds = true
        sendBtn.layer.cornerRadius = 8
        sendBtn.addTarget(self, action: #selector(sendDiary), for: .touchUpInside)
        sendBtn.isUserInteractionEnabled = false
    }
    
    
    @objc func sendDiary(){
        //IP是119.3.154.207，端口是8080
        print("post")
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/diary/post", method: .post, parameter: nil)
        let user_id = UserDefaults.standard.string(forKey: "email")
        let currentDiary = Diary(user_id: user_id!, diary: Diary.diary_struct(user_id: user_id!, create_at: "", diary_code: "", hash_tag: tagField.text!, content: textView.text))
        let response = NetworkMgr.shared.request(API: webAPI, parameters: currentDiary, headers: nil)
        response.responseDict { result in
            switch result {
            case .success(let model):
                let status = model["status"] as! Int
                if status == 1 {
                    DispatchQueue.main.async {
                        self.sendStatus(flag: true)
                    }
                }else{
                    DispatchQueue.main.async {
                        self.sendStatus(flag: false)
                    }
                }
            case .failure(_):
                break
            }
        }
    }
    
    private func sendStatus(flag:Bool){
        var msg:String
        if flag {
            tagField.text = ""
            textView.text = ""
            msg = "成功啦，坚持写日记是好习惯呢"
            sendBtn.isUserInteractionEnabled = false
            sendBtn.backgroundColor = .lightGray
        }else{
            msg = "不小心失败了呢，再试试吧"
        }
        let alertView = UIAlertController.init(title: "提示", message: msg, preferredStyle: .alert)
        let alert = UIAlertAction.init(title: "确定", style: .default) { (UIAlertAction) in
            
        }
        alertView.addAction(alert)
        self.present(alertView, animated: true, completion: nil)
    }
    
    @objc func gotoAllDiary(){
        let vc = AllDiaryViewController()
        vc.modalPresentationStyle = .fullScreen
        self.present(vc, animated: true, completion: nil)
    }
    
    private func setupTextView(){
        self.view.addSubview(tagField)
        tagField.textColor = .black
        let attributes:[NSAttributedString.Key:Any] = [.foregroundColor: UIColor.darkGray]
        let attributedString = NSMutableAttributedString(string: "#请输入tag", attributes: attributes)
        tagField.attributedPlaceholder = attributedString
        tagField.snp.makeConstraints { make in
            make.bottom.equalTo(profile.snp.bottom)
            make.left.equalTo(profile.snp.right).offset(20)
            make.width.equalTo(200)
            make.height.equalTo(50)
        }
        tagField.leftView = UIView(frame: CGRect(x: 0, y: 0, width: 12, height: 0))
        tagField.leftViewMode = .always
        tagField.layer.masksToBounds = true
        tagField.layer.cornerRadius = 10
        tagField.layer.borderColor = CGColor(red: 1, green: 1, blue: 1, alpha: 1)
        tagField.layer.borderWidth = 4
        
        self.view.addSubview(textView)
        textView.textColor = .black
        textView.snp.makeConstraints { make in
            make.top.equalTo(profile.snp.bottom).offset(30)
            make.width.equalToSuperview().multipliedBy(0.90)
            make.height.equalToSuperview().multipliedBy(0.50)
            make.centerX.equalToSuperview()
        }
        textView.backgroundColor = .clear
        textView.layer.masksToBounds = true
        textView.layer.cornerRadius = 20
        textView.layer.borderWidth = 8
        textView.layer.borderColor = CGColor(red: 1, green: 1, blue: 1, alpha: 1)
        textView.font = UIFont.systemFont(ofSize: 20)
        textView.contentInset = UIEdgeInsets(top: 10, left: 10, bottom: -10, right: -10)
    }
    
    private func setupProfile(){
        let data = UserDefaults.standard.data(forKey: "profile")
        let image = UIImage(data: data!)!
        profile.image = image
        self.view.addSubview(profile)
        profile.layer.masksToBounds = true
        profile.layer.cornerRadius = 18
        profile.snp.makeConstraints { make in
            make.top.equalToSuperview().offset(80)
            make.left.equalToSuperview().offset(40)
            make.height.width.equalTo(120)
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
        checkIsEmpty()
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        textView.resignFirstResponder()
        tagField.resignFirstResponder()
    }

}

extension CreateDiaryViewController:UITextViewDelegate,UITextFieldDelegate{
//    func textView(_ textView: UITextView, shouldChangeTextIn range: NSRange, replacementText text: String) -> Bool {
//        if text == "\n" {
//            self.view?.endEditing(false)
//            return false
//        }
//        return true
//    }
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    
    func textViewDidEndEditing(_ textView: UITextView) {
        if tagField.text?.count != 0 && textView.text.count != 0 {
            sendBtn.isUserInteractionEnabled = true
            sendBtn.backgroundColor = UIColor(red: 231/255.0, green: 124/255.0, blue: 142/255.0, alpha: 1)
        }else{
            sendBtn.isUserInteractionEnabled = false
            sendBtn.backgroundColor = .lightGray
        }
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        if tagField.text?.count != 0 && textView.text.count != 0 {
            sendBtn.isUserInteractionEnabled = true
            sendBtn.backgroundColor = UIColor(red: 231/255.0, green: 124/255.0, blue: 142/255.0, alpha: 1)
        }else{
            sendBtn.isUserInteractionEnabled = false
            sendBtn.backgroundColor = .lightGray
        }
    }
}
