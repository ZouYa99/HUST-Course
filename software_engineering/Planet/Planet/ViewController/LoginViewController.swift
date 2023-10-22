//
//  LoginViewController.swift
//  Planet
//
//  Created by ZouYa on 2021/12/19.
//

import UIKit

class LoginViewController: UIViewController {
    
    var homeBtn = UIButton()
    var appIcon = UIImageView()
    
    var emailField = UITextField()
    var passwordField = UITextField()
    
    var registerBtn = UIButton()
    var forgetPasswordBtn = UIButton()
    var confirmBtn = UIButton()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.view.backgroundColor = UIColor(red:36/255.0, green: 134/255.0, blue: 185/255.0, alpha: 1.0)
        emailField.delegate = self
        passwordField.delegate = self
        emailField.returnKeyType = .done
        passwordField.returnKeyType = .done
        setupHomeBtn()
        setupAppIcon()
        setupTextField()
        setupBtn()
    }
    
    private func setupBtn(){
        self.view.addSubview(registerBtn)
        registerBtn.backgroundColor = .clear
        registerBtn.setTitle("立即注册", for: .normal)
        registerBtn.setTitleColor(.black, for: .normal)
        registerBtn.layer.masksToBounds = true
        registerBtn.layer.cornerRadius = 8
        registerBtn.snp.makeConstraints { make in
            make.left.equalTo(passwordField.snp.left).offset(10)
            make.width.equalTo(100)
            make.height.equalTo(40)
            make.top.equalTo(passwordField.snp.bottom).offset(20)
        }
        registerBtn.addTarget(self, action: #selector(goToRegister), for: .touchUpInside)
        
        self.view.addSubview(forgetPasswordBtn)
        forgetPasswordBtn.backgroundColor = .clear
        forgetPasswordBtn.setTitle("忘记密码", for: .normal)
        forgetPasswordBtn.setTitleColor(.black, for: .normal)
        forgetPasswordBtn.layer.masksToBounds = true
        forgetPasswordBtn.layer.cornerRadius = 8
        forgetPasswordBtn.snp.makeConstraints { make in
            make.right.equalTo(passwordField.snp.right).offset(-10)
            make.width.equalTo(100)
            make.height.equalTo(40)
            make.top.equalTo(passwordField.snp.bottom).offset(20)
        }
        forgetPasswordBtn.addTarget(self, action: #selector(goToForget), for: .touchUpInside)
        
        self.view.addSubview(confirmBtn)
        confirmBtn.backgroundColor = .lightGray
        confirmBtn.setTitle("确认", for: .normal)
        confirmBtn.setTitleColor(.black, for: .normal)
        confirmBtn.layer.masksToBounds = true
        confirmBtn.layer.cornerRadius = 6
        confirmBtn.snp.makeConstraints { make in
            make.centerX.equalToSuperview()
            make.top.equalTo(forgetPasswordBtn.snp.bottom).offset(50)
            make.width.equalTo(80)
            make.height.equalTo(40)
        }
        confirmBtn.isUserInteractionEnabled = false
        confirmBtn.addTarget(self, action: #selector(confirmToPost), for: .touchUpInside)
    }
    
    @objc func confirmToPost(){
        //IP是119.3.154.207，端口是8080
        print("post")
        let webAPI = WebAPI(path: "http://119.3.154.207:8080/login/login", method: .post, parameter: nil)
        let response = NetworkMgr.shared.request(API: webAPI, parameters: ["email":emailField.text,"password":passwordField.text], headers: nil)
        response.responseDict { result in
            switch result {
            case .success(let model):
                let status = model["status"] as! Int
                if status == 1 {
                    let msg = model["msg"] as! [String:String]
                    let userName = msg["user_name"]!
                    let email = msg["user_email"]!
                    let password = msg["user_password"]!
                    UserDefaults.standard.set(userName, forKey: "userName")
                    UserDefaults.standard.set(email, forKey: "email")
                    UserDefaults.standard.set(password, forKey: "password")
                    NotificationCenter.default.post(name: .init(rawValue: "login success"), object: nil)
                    DispatchQueue.main.async {
                        self.dismiss(animated: true, completion: nil)
                    }
                }else{
                    DispatchQueue.main.async {
                        self.presentAlert()
                    }
                }
            case .failure(_):
                break
            }
        }
    }
    
    private func presentAlert(){
        let alertView = UIAlertController.init(title: "提示", message: "登录失败！是不是忘记注册了呢", preferredStyle: .alert)
        let alert = UIAlertAction.init(title: "确定", style: .default) { (UIAlertAction) in
            
        }
        alertView.addAction(alert)
        self.present(alertView, animated: true, completion: nil)
    }
    
    @objc func goToRegister(){
        let vc = RegisterViewController()
        vc.modalPresentationStyle = .fullScreen
        self.present(vc, animated: true, completion: nil)
    }
    
    @objc func goToForget(){
        let vc = ForgetPasswordViewController()
        vc.modalPresentationStyle = .fullScreen
        self.present(vc, animated: true, completion: nil)
    }
    
    private func setupAppIcon(){
        self.view.addSubview(appIcon)
        appIcon.image = UIImage(named: "app")
        let mutiply = CGFloat(appIcon.image!.size.height) / CGFloat(appIcon.image!.size.width)
        appIcon.snp.makeConstraints { make in
            make.top.equalToSuperview().offset(100)
            make.centerX.equalToSuperview()
            make.width.equalTo(240)
            make.height.equalTo(mutiply*240)
        }
        appIcon.layer.masksToBounds = true
        appIcon.layer.cornerRadius = 20
    }
    
    private func setupTextField(){
        let attributes:[NSAttributedString.Key:Any] = [.foregroundColor: UIColor.darkGray]
        
        let attributedString1 = NSMutableAttributedString(string: "请输入邮箱", attributes: attributes)
        self.view.addSubview(emailField)
        emailField.attributedPlaceholder = attributedString1
        emailField.backgroundColor = .white
        emailField.leftView = UIView(frame: CGRect(x: 0, y: 0, width: 10, height: 0))
        emailField.leftViewMode = .always
        emailField.textColor = .black
        emailField.layer.masksToBounds = true
        emailField.layer.cornerRadius = 10
        emailField.snp.makeConstraints { make in
            make.top.equalTo(appIcon.snp.bottom).offset(50)
            make.left.equalToSuperview().offset(50)
            make.width.equalTo(300)
            make.height.equalTo(60)
        }
        
        self.view.addSubview(passwordField)
        let attributedString2 = NSMutableAttributedString(string: "请输入密码", attributes: attributes)
        passwordField.attributedPlaceholder = attributedString2
        passwordField.backgroundColor = .white
        passwordField.leftView = UIView(frame: CGRect(x: 0, y: 0, width: 10, height: 0))
        passwordField.leftViewMode = .always
        passwordField.layer.masksToBounds = true
        passwordField.layer.cornerRadius = 10
        passwordField.textColor = .black
        passwordField.isSecureTextEntry = true
        passwordField.snp.makeConstraints { make in
            make.top.equalTo(emailField.snp.bottom).offset(20)
            make.left.equalToSuperview().offset(50)
            make.width.equalTo(300)
            make.height.equalTo(60)
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
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        emailField.resignFirstResponder()
        passwordField.resignFirstResponder()
    }

}

extension LoginViewController:UITextFieldDelegate{
    func textFieldDidEndEditing(_ textField: UITextField) {
        if emailField.text?.count != 0 && passwordField.text?.count != 0 {
            confirmBtn.isUserInteractionEnabled = true
            confirmBtn.backgroundColor = UIColor(red: 231/255.0, green: 124/255.0, blue: 142/255.0, alpha: 1)
        }else{
            confirmBtn.isUserInteractionEnabled = true
            confirmBtn.backgroundColor = .lightGray
        }
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
}
