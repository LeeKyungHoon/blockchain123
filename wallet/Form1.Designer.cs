namespace wallet
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.To_Address = new System.Windows.Forms.Label();
            this.Value = new System.Windows.Forms.Label();
            this.Fee = new System.Windows.Forms.Label();
            this.genKey = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // To_Address
            // 
            this.To_Address.AutoSize = true;
            this.To_Address.Font = new System.Drawing.Font("HY견고딕", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.To_Address.Location = new System.Drawing.Point(57, 67);
            this.To_Address.Name = "To_Address";
            this.To_Address.Size = new System.Drawing.Size(178, 27);
            this.To_Address.TabIndex = 0;
            this.To_Address.Text = "To Address";
            this.To_Address.Click += new System.EventHandler(this.label1_Click);
            // 
            // Value
            // 
            this.Value.AutoSize = true;
            this.Value.Font = new System.Drawing.Font("HY견고딕", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.Value.Location = new System.Drawing.Point(57, 121);
            this.Value.Name = "Value";
            this.Value.Size = new System.Drawing.Size(93, 27);
            this.Value.TabIndex = 0;
            this.Value.Text = "Value";
            this.Value.Click += new System.EventHandler(this.label1_Click);
            // 
            // Fee
            // 
            this.Fee.AutoSize = true;
            this.Fee.Font = new System.Drawing.Font("HY견고딕", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.Fee.Location = new System.Drawing.Point(57, 177);
            this.Fee.Name = "Fee";
            this.Fee.Size = new System.Drawing.Size(64, 27);
            this.Fee.TabIndex = 0;
            this.Fee.Text = "Fee";
            this.Fee.Click += new System.EventHandler(this.label1_Click);
            // 
            // genKey
            // 
            this.genKey.Font = new System.Drawing.Font("HY견고딕", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.genKey.Location = new System.Drawing.Point(163, 405);
            this.genKey.Name = "genKey";
            this.genKey.Size = new System.Drawing.Size(211, 33);
            this.genKey.TabIndex = 1;
            this.genKey.Text = "Generate New Key";
            this.genKey.UseVisualStyleBackColor = true;
            this.genKey.Click += new System.EventHandler(this.genKey_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("HY견고딕", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label1.Location = new System.Drawing.Point(57, 229);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(171, 27);
            this.label1.TabIndex = 0;
            this.label1.Text = "PrivateKey";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("HY견고딕", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label2.Location = new System.Drawing.Point(57, 286);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(160, 27);
            this.label2.TabIndex = 0;
            this.label2.Text = "PublicKey";
            this.label2.Click += new System.EventHandler(this.label1_Click);
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("HY견고딕", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.button1.Location = new System.Drawing.Point(454, 365);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(131, 33);
            this.button1.TabIndex = 1;
            this.button1.Text = "Save Key";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.genKey_Click);
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("HY견고딕", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.button2.Location = new System.Drawing.Point(454, 405);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(131, 33);
            this.button2.TabIndex = 1;
            this.button2.Text = "Load Key";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.genKey_Click);
            // 
            // button3
            // 
            this.button3.Font = new System.Drawing.Font("HY견고딕", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.button3.Location = new System.Drawing.Point(657, 326);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(131, 33);
            this.button3.TabIndex = 1;
            this.button3.Text = "Save Tx";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.genKey_Click);
            // 
            // button4
            // 
            this.button4.Font = new System.Drawing.Font("HY견고딕", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.button4.Location = new System.Drawing.Point(657, 365);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(131, 33);
            this.button4.TabIndex = 1;
            this.button4.Text = "Sign Tx";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.genKey_Click);
            // 
            // button5
            // 
            this.button5.Font = new System.Drawing.Font("HY견고딕", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.button5.Location = new System.Drawing.Point(625, 405);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(163, 33);
            this.button5.TabIndex = 1;
            this.button5.Text = "Broadcast Tx";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.genKey_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.genKey);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Fee);
            this.Controls.Add(this.Value);
            this.Controls.Add(this.To_Address);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label To_Address;
        private System.Windows.Forms.Label Value;
        private System.Windows.Forms.Label Fee;
        private System.Windows.Forms.Button genKey;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
    }
}

