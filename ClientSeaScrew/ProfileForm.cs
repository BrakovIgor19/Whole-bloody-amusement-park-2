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
    public partial class ProfileForm : Form
    {
        private AuthorizationForm authorizationForm;

        public ProfileForm(AuthorizationForm authorizationForm)
        {
            this.authorizationForm = authorizationForm;
            InitializeComponent();
        }

        private void buttonToChat_Click(object sender, EventArgs e)
        {
            this.Hide();
            authorizationForm.chatForm.Show();
        }

        private void buttonExitToAuthorization_Click(object sender, EventArgs e)
        {
            authorizationForm.ExitToAthorization();
            this.Hide();
            authorizationForm.Show();
        }
    }
}
