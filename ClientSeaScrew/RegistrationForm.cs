using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientSeaScrew
{
    public partial class RegistrationForm : Form
    {
        private AuthorizationForm authorizationForm;
        public RegistrationForm(AuthorizationForm authorizationForm)
        {
            this.authorizationForm = authorizationForm;
            InitializeComponent();
        }

        private void buttonRegistr_Click(object sender, EventArgs e)
        {
            //authorizationForm.ExitToAthorization();
            this.Hide();
            authorizationForm.Show();
        }

        private void RegistrationForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (authorizationForm.client != null && authorizationForm.client.isValid)
            {
                authorizationForm.CloseAll();
            }
        }
    }
}
