import java.io.*;
import java.util.*;

class rec01{
    Vector<String> population = new Vector<String>();
    String file_path = System.getProperty("user.dir") + "/Rec01/life.txt";
    int map_width;

    public void pre_process() throws IOException{
        BufferedReader br = null;
        try {
            System.out.println(file_path);
            br = new BufferedReader(new FileReader(file_path));
            String line;
            line = br.readLine();
            map_width = line.length() + 2;
            StringBuilder sb = new StringBuilder();
            for(int i = 0; i < map_width; i++){
                sb.append("-");
            }
            population.add(sb.toString());
            population.add("-" + line + "-");
            while ((line = br.readLine()) != null) {
                population.add("-" + line + "-");
            }
            population.add(sb.toString());
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            br.close();
        }
    }

    public void print_map(){
        for(int i = 1; i < population.size() - 1; ++i){
            for(int j = 1; j < map_width - 1; ++j ){
                System.out.print(population.get(i).charAt(j));
            }
            System.out.println();
        }
    }

    public char is_alive(int row, int col){
        int alive_neighbors = 0;
        for(int i = -1; i < 2; ++i){
            for(int j = -1; j < 2; ++j){
                if(population.get(row + i).charAt(col + j) == '*'){
                    alive_neighbors++;
                }
            }
        }
        if(population.get(row).charAt(col) == '*'){
            if(alive_neighbors == 3 || alive_neighbors == 4){
                return '*';
            }
        }else{
            if(alive_neighbors == 3){
                return '*';
            }
        }
        return '-';
    }

    public void transition(){
        Vector<String> new_world = new Vector<String>(population);
        for (int i = 1; i < population.size() - 1; ++i) {
            StringBuilder sb = new StringBuilder();
            sb.append('-');
            for (int j = 1; j < map_width - 1; ++j) {
                sb.append(this.is_alive(i, j));
            }
            sb.append('-');
            new_world.set(i, sb.toString());
        }
        population = new_world;
    }

    public rec01(){
        System.out.println("Game of life begins");
    }

    public static void main(String[] args) throws IOException{
        System.out.println("in rec01");
        // rec01 r = new rec01();
        rec01 r = new rec01();
        r.pre_process();
        r.print_map();
        for(int i = 1; i < 11; i++){
            System.out.println(i + " Generation:");
            r.transition();
            r.print_map();
        }
    }
}