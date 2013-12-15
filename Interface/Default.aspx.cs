using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Runtime;
using Wrapper;

namespace Interface
{
    public partial class _Default : System.Web.UI.Page
    {
        public void price(object sender, EventArgs e)
        {
            // Récupérer les valeurs des paramètres dans les différentes TextBox
            WrapperClass wc = new WrapperClass();
            double strik = double.Parse(strike.Text);
            int siz = int.Parse(size.Text);
            double taux = double.Parse(r.Text);
            double he = double.Parse(h.Text);
            int sample = int.Parse(samples.Text);

            //byte[] abyte1 = new byte[type.Text.Length];
            //System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();
            //abyte1 = encoding.GetBytes(type.Text);
            //sbyte[] baske = Array.ConvertAll(abyte1, q => Convert.ToSByte(q));
            String baske = "basket";
            double[] sigm = new double[1];
            sigm[0] = double.Parse(sigma.Text);
            double[] ro = new double[1];
            ro[0] = double.Parse(rho.Text);
            
            wc.getPriceOption(sample, baske, siz, taux, ro, strik, sigm);
            Label2.Text = wc.getPrice().ToString();
            Label.Text = wc.getIC().ToString();
        }
    }
}
