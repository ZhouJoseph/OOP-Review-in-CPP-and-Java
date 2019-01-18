import java.util.*;
import java.io.*;

public class hw01{
    String dir = System.getProperty("user.dir");
    String file_path;
    Vector<String> lines = new Vector<String>();
    int step;

    private char decrypt_char(char c){
        int to_be_decrypted = (int) c;
        int a = (int) 'a';
        int z = (int) 'z';
        char res;
        if(to_be_decrypted >= a && to_be_decrypted <= z){
            if (to_be_decrypted - a - step >= 0) {
                res = (char) (to_be_decrypted - step);
            }else{
                res = (char) ( z + (to_be_decrypted - a - step) + 1);
            }
        }else{
            res = c;
        }
        return res;
    }

    private String decrypt_string(String s){
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < s.length(); i++){
            sb.append(this.decrypt_char(s.charAt(i)));
        }
        return sb.toString();
    }

    public void decrypt_file(){
        for(int i = 0; i < lines.size(); ++i){
            lines.set(i, this.decrypt_string(lines.get(i)));
        }
        System.out.println(lines);
    }

    public hw01(String file_name) throws IOException{
        file_path = dir + "/HW01/" + file_name;
        BufferedReader br = null;
        try{
            br = new BufferedReader(new FileReader(file_path));
            String line;
            while((line = br.readLine()) != null){
                lines.add(line);
            }
        } catch(IOException e){
            e.printStackTrace();
        } finally{
            br.close();
            step = Integer.parseInt(lines.get(0));
            System.out.println(lines);
        }
    }
    
    public static void main(String[] args) throws IOException{
        hw01 hw = new hw01("file.txt");
        hw.decrypt_file();
    }
}